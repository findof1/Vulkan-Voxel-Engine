
#ifndef CHUNK_DATA_H
#define CHUNK_DATA_H
#include "blockType.h"
#include "world.h"
#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class ChunkData
{
public:
  std::vector<BlockType> blocks;
  int chunkSize = 16;
  int chunkHeight = 100;
  World *world;
  glm::vec3 worldPosition;
  bool modifiedChunk = false;

  ChunkData(World *world, glm::vec3 worldPosition, int chunkSize, int chunkHeight);
};

#endif