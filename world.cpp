#include "blockType.h"
#include "chunkData.h"
#include "chunkUtils.h"
#include "chunkRenderer.h"
#include <map>
#include <glm/glm.hpp>

World::World() {}

void World::generateWorld(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices)
{
  chunkDataDictionary.clear();
  chunkDictionary.clear();

  for (int x = 0; x < mapSizeInChunks; x++)
  {
    for (int z = 0; z < mapSizeInChunks; z++)
    {

      ChunkData data = ChunkData(this, glm::vec3(x * chunkSize, 0, z * chunkSize), chunkSize, chunkHeight);
      generateVoxels(data);
      chunkDataDictionary[data.worldPosition] = data;
    }
  }

  for (auto &entry : chunkDataDictionary)
  {
    ChunkData &data = entry.second;

    MeshData meshData = getChunkMeshData(data);

    ChunkRenderer chunkRenderer(data);
    chunkDictionary[data.worldPosition] = chunkRenderer;
    chunkRenderer.updateChunk(vertices, indices);
  }
}

void World::generateVoxels(const ChunkData &data)
{
}

BlockType World::getBlockFromChunkCoordinates(const ChunkData &chunkData, int x, int y, int z)
{
  glm::vec3 pos = chunkPositionFromBlockCoords(this, x, y, z);

  auto it = chunkDataDictionary.find(pos);
  if (it == chunkDataDictionary.end())
  {
    return BlockType::Nothing;
  }

  ChunkData &containerChunk = it->second;

  glm::vec3 blockInChunkCoordinates = getBlockInChunkCoordinates(containerChunk, glm::vec3(x, y, z));
  return getBlockFromChunkCoordinates(containerChunk, blockInChunkCoordinates.x, blockInChunkCoordinates.y, blockInChunkCoordinates.z);
}
