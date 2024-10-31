#include "blockType.h"
#include "chunkData.h"
#include "chunkUtils.h"
#include "chunkRenderer.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <cmath>
#include <chrono>
#include <random>

World::World() {}

void World::generateWorld(std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{
  chunkDataDictionary.clear();
  vertices->clear();
  indices->clear();
  chunkDictionary.clear();

  BlockDataSO textureDataSource(0.1, 0.1);

  TextureData grassTexture;
  grassTexture.up = glm::vec2(8, 9);
  grassTexture.down = glm::vec2(7, 4);
  grassTexture.side = glm::vec2(7, 5);
  grassTexture.blockType = BlockType::Grass_Dirt;

  TextureData dirtTexture;
  dirtTexture.up = glm::vec2(7, 4);
  dirtTexture.down = glm::vec2(7, 4);
  dirtTexture.side = glm::vec2(7, 4);
  dirtTexture.blockType = BlockType::Dirt;

  TextureData waterTexture;
  waterTexture.up = glm::vec2(0, 3);
  waterTexture.down = glm::vec2(0, 3);
  waterTexture.side = glm::vec2(0, 3);
  waterTexture.blockType = BlockType::Water;

  TextureData sandTexture;
  sandTexture.up = glm::vec2(3, 3);
  sandTexture.down = glm::vec2(3, 3);
  sandTexture.side = glm::vec2(3, 3);
  sandTexture.blockType = BlockType::Sand;

  TextureData stoneTexture;
  stoneTexture.up = glm::vec2(3, 5);
  stoneTexture.down = glm::vec2(3, 5);
  stoneTexture.side = glm::vec2(3, 5);
  stoneTexture.blockType = BlockType::Stone;

  TextureData treeTrunkTexture;
  treeTrunkTexture.up = glm::vec2(0, 0);
  treeTrunkTexture.down = glm::vec2(0, 0);
  treeTrunkTexture.side = glm::vec2(1, 9);
  treeTrunkTexture.blockType = BlockType::TreeTrunk;

  TextureData treeLeafesSolidTexture;
  treeLeafesSolidTexture.up = glm::vec2(5, 8);
  treeLeafesSolidTexture.down = glm::vec2(5, 8);
  treeLeafesSolidTexture.side = glm::vec2(5, 8);
  treeLeafesSolidTexture.blockType = BlockType::TreeLeafesSolid;

  textureDataSource.textureDataList.push_back(grassTexture);
  textureDataSource.textureDataList.push_back(dirtTexture);
  textureDataSource.textureDataList.push_back(waterTexture);
  textureDataSource.textureDataList.push_back(sandTexture);
  textureDataSource.textureDataList.push_back(stoneTexture);
  textureDataSource.textureDataList.push_back(treeTrunkTexture);
  textureDataSource.textureDataList.push_back(treeLeafesSolidTexture);

  BlockDataManager blockManager(&textureDataSource);

  for (int x = 0; x < mapSizeInChunks; x++)
  {
    for (int z = 0; z < mapSizeInChunks; z++)
    {

      ChunkData *data = new ChunkData(this, glm::vec3(x * chunkSize, 0, z * chunkSize), chunkSize, chunkHeight);
      generateVoxels(data);

      chunkDataDictionary.emplace(std::make_pair(glm::ivec3(data->worldPosition), *data));
    }
  }
  int count = 0;
  for (auto &entry : chunkDataDictionary)
  {
    ChunkData *data = &entry.second;

    ChunkRenderer chunkRenderer(data);
    chunkDictionary[data->worldPosition] = chunkRenderer;

    MeshData meshData = getChunkMeshData(chunkRenderer.chunkData, vertices->size());

    chunkRenderer.updateChunk(&meshData, vertices, indices);

    count++;
    std::cout << "Count: " << count << std::endl;
  }
}

void World::generateVoxels(ChunkData *data)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(1, 2);
  std::mt19937 treeGen(rd());
  std::uniform_real_distribution<float> treeDistribution(0.0f, 1.0f);

  int chunkSize = data->chunkSize;

  for (int x = 0; x < chunkSize; x++)
  {
    for (int z = 0; z < chunkSize; z++)
    {
      float noiseValue = glm::perlin(glm::vec2((data->worldPosition.x + x) * noiseScale, (data->worldPosition.z + z) * noiseScale)) + 1;
      int groundPosition = static_cast<int>(std::round(noiseValue * (chunkHeight / 2)));

      float treeDensity = (glm::perlin(glm::vec2((data->worldPosition.x + x) * treeNoiseScale, (data->worldPosition.z + z) * treeNoiseScale)) + 1) / 16;
      float randomTreeValue = treeDistribution(treeGen);
      bool shouldPlaceTree = randomTreeValue < treeDensity;

      for (int y = 0; y < chunkHeight; y++)
      {
        BlockType voxelType;

        if (y > groundPosition)
        {

          if (y < waterThreshold)
          {
            voxelType = BlockType::Water;
          }
          else if (y == groundPosition + 1 && shouldPlaceTree)
          {
            voxelType = BlockType::TreeTrunk;
            setBlock(data, glm::ivec3(x, y + 1, z), voxelType);
            setBlock(data, glm::ivec3(x, y + 2, z), voxelType);
            setBlock(data, glm::ivec3(x, y + 3, z), voxelType);
            setBlock(data, glm::ivec3(x, y + 4, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 4, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 4, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 4, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 4, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 4, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 4, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 4, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 4, z - 1), BlockType::TreeLeafesSolid);

            setBlock(data, glm::ivec3(x + 1, y + 3, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 3, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 3, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 3, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 3, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 3, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 3, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 3, z - 1), BlockType::TreeLeafesSolid);

            setBlock(data, glm::ivec3(x + 2, y + 3, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 3, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 3, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 3, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 3, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 3, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 3, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 3, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 3, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 3, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 3, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 3, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 3, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 3, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 3, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 3, z), BlockType::TreeLeafesSolid);

            setBlock(data, glm::ivec3(x + 2, y + 2, z), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 2, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 2, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 2, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 2, y + 2, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 2, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x + 1, y + 2, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 2, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x, y + 2, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 2, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 1, y + 2, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 2, z - 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 2, z + 2), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 2, z - 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 2, z + 1), BlockType::TreeLeafesSolid);
            setBlock(data, glm::ivec3(x - 2, y + 2, z), BlockType::TreeLeafesSolid);
          }
          else
          {
            voxelType = BlockType::Air;
          }
        }
        else
        {
          int randomNum = distribution(gen);

          if (y == groundPosition)
          {

            if (y < waterThreshold)
            {
              voxelType = BlockType::Sand;
            }
            else
            {
              voxelType = BlockType::Grass_Dirt;
            }
          }
          else
          {
            if (y < waterThreshold)
            {
              voxelType = BlockType::Sand;
            }
            else if (y < groundPosition - 7)
            {
              voxelType = BlockType::Stone;
            }
            else
            {
              voxelType = BlockType::Dirt;
            }
          }
        }

        setBlock(data, glm::ivec3(x, y, z), voxelType);
      }
    }
  }
}

BlockType World::worldGetBlockFromChunkCoordinates(ChunkData *chunkData, int x, int y, int z)
{

  glm::vec3 pos = chunkPositionFromBlockCoords(this, x, y, z);

  auto it = chunkDataDictionary.find(pos);
  if (it == chunkDataDictionary.end())
  {
    return BlockType::Nothing;
  }

  ChunkData *containerChunk = &it->second;

  glm::vec3 blockInChunkCoordinates = getBlockInChunkCoordinates(containerChunk, glm::vec3(x, y, z));

  if (blockInChunkCoordinates.x < 0 || blockInChunkCoordinates.y < 0 || blockInChunkCoordinates.z < 0 ||
      blockInChunkCoordinates.x >= containerChunk->chunkSize || blockInChunkCoordinates.y >= containerChunk->chunkHeight || blockInChunkCoordinates.z >= containerChunk->chunkSize)
  {
    std::cout << "Invalid block coordinates!" << std::endl;
    return BlockType::Nothing;
  }

  return getBlockFromChunkCoordinates(containerChunk, blockInChunkCoordinates.x, blockInChunkCoordinates.y, blockInChunkCoordinates.z);
}
