#include "blockType.h"
#include "chunkData.h"
#include "chunkUtils.h"
#include "chunkRenderer.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <cmath>
#include <chrono>

World::World() {}

void World::generateWorld(std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{
  chunkDataDictionary.clear();
  vertices->clear();
  indices->clear();
  chunkDictionary.clear();

  for (int x = 0; x < mapSizeInChunks; x++)
  {
    for (int z = 0; z < mapSizeInChunks; z++)
    {

      ChunkData *data = new ChunkData(this, glm::vec3(x * chunkSize, 0, z * chunkSize), chunkSize, chunkHeight);
      generateVoxels(data);

      chunkDataDictionary.emplace(std::make_pair(glm::ivec3(data->worldPosition), *data));
    }
  }

  for (auto &entry : chunkDataDictionary)
  {
    auto start = std::chrono::high_resolution_clock::now();
    ChunkData *data = &entry.second;

    ChunkRenderer chunkRenderer(data);
    chunkDictionary[data->worldPosition] = chunkRenderer;

    MeshData meshData = getChunkMeshData(chunkRenderer.chunkData, indices->size());

    chunkRenderer.updateChunk(&meshData, vertices, indices);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for operations: " << elapsed.count() << " seconds." << std::endl;
  }
}

void World::generateVoxels(ChunkData *data)
{
  for (int x = 0; x < data->chunkSize; x++)
  {
    for (int z = 0; z < data->chunkSize; z++)
    {
      float noiseValue = glm::perlin(glm::vec2((data->worldPosition.x + x) * noiseScale, (data->worldPosition.z + z) * noiseScale));
      int groundPosition = static_cast<int>(std::round(noiseValue * chunkHeight)) + 15;
      for (int y = 0; y < chunkHeight; y++)
      {
        BlockType voxelType = BlockType::Dirt;
        if (y > groundPosition)
        {
          if (y < waterThreshold)
          {
            voxelType = BlockType::Water;
          }
          else
          {
            voxelType = BlockType::Air;
          }
        }
        else if (y == groundPosition)
        {
          voxelType = BlockType::Grass_Dirt;
        }

        setBlock(data, glm::ivec3(x, y, z), voxelType);
      }
    }
  }
}

BlockType World::getBlockFromChunkCoordinates(ChunkData *chunkData, int x, int y, int z, int depth)
{
  if (depth > 14)
  {
    return BlockType::Nothing;
  }

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

  return getBlockFromChunkCoordinates(containerChunk, blockInChunkCoordinates.x, blockInChunkCoordinates.y, blockInChunkCoordinates.z, depth + 1);
}
