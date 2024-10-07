#include "chunkData.h"

ChunkData::ChunkData(World *world, glm::vec3 worldPosition, int chunkSize = 16, int chunkHeight = 100) : chunkSize(chunkSize), chunkHeight(chunkHeight), worldPosition(worldPosition), world(world)
{
  blocks.reserve(chunkSize * chunkHeight * chunkSize);
}