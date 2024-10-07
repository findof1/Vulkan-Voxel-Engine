#ifndef CHUNK_DATA_H
#define CHUNK_DATA_H
#include "blockType.h"
#include "world.h"
#include <vector>
#include <glm/glm.hpp>

class World;
class ChunkData
{
public:
  std::vector<BlockType> blocks;
  int chunkSize = 16;
  int chunkHeight = 100;
  World *world;
  glm::vec3 worldPosition;
  bool modifiedChunk = false;
  ChunkData() = default;
  ChunkData(const ChunkData &other) = default;
  ChunkData(ChunkData &&other) noexcept = default;
  ChunkData &operator=(const ChunkData &other) = default;
  ChunkData &operator=(ChunkData &&other) noexcept = default;
  ChunkData(World *world, glm::vec3 worldPosition, int chunkSize, int chunkHeight);
};

#endif