
#include <vector>
#include <functional>
#include <stdexcept>
#include <glm/glm.hpp>
#include "chunkData.h"
#include "blockType.h"
#include "meshData.h"
#include "blockHelper.h"

glm::ivec3 getPositionFromIndex(const ChunkData &chunkData, int index)
{
  int x = index % chunkData.chunkSize;
  int y = (index / chunkData.chunkSize) % chunkData.chunkHeight;
  int z = index / (chunkData.chunkSize * chunkData.chunkHeight);
  return {x, y, z};
}

void loopThroughTheBlocks(const ChunkData &chunkData, std::function<void(int, int, int)> actionToPerform)
{
  for (size_t index = 0; index < chunkData.blocks.size(); ++index)
  {
    glm::ivec3 position = getPositionFromIndex(chunkData, index);
    actionToPerform(position.x, position.y, position.z);
  }
}

bool inRange(const ChunkData &chunkData, int axisCoordinate)
{
  return axisCoordinate >= 0 && axisCoordinate < chunkData.chunkSize;
}

bool inRangeHeight(const ChunkData &chunkData, int ycoordinate)
{
  return ycoordinate >= 0 && ycoordinate < chunkData.chunkHeight;
}

BlockType getBlockFromChunkCoordinates(const ChunkData &chunkData, glm::ivec3 chunkCoordinates)
{
  return getBlockFromChunkCoordinates(chunkData, chunkCoordinates.x, chunkCoordinates.y, chunkCoordinates.z);
}

BlockType getBlockFromChunkCoordinates(const ChunkData &chunkData, int x, int y, int z)
{
  if (inRange(chunkData, x) && inRangeHeight(chunkData, y) && inRange(chunkData, z))
  {
    int index = getIndexFromPosition(chunkData, x, y, z);
    return chunkData.blocks[index];
  }

  return chunkData.world->getBlockFromChunkCoordinates(chunkData, chunkData.worldPosition.x + x, chunkData.worldPosition.y + y, chunkData.worldPosition.z + z);
}

void setBlock(ChunkData &chunkData, const glm::ivec3 &localPosition, BlockType block)
{
  if (inRange(chunkData, localPosition.x) && inRangeHeight(chunkData, localPosition.y) && inRange(chunkData, localPosition.z))
  {
    int index = getIndexFromPosition(chunkData, localPosition.x, localPosition.y, localPosition.z);
    chunkData.blocks[index] = block;
  }
  else
  {
    throw std::runtime_error("Need to ask World for appropriate chunk");
  }
}

int getIndexFromPosition(const ChunkData &chunkData, int x, int y, int z)
{
  return x + chunkData.chunkSize * y + chunkData.chunkSize * chunkData.chunkHeight * z;
}

glm::ivec3 getBlockInChunkCoordinates(const ChunkData &chunkData, const glm::ivec3 &pos)
{
  return glm::ivec3{
      pos.x - chunkData.worldPosition.x,
      pos.y - chunkData.worldPosition.y,
      pos.z - chunkData.worldPosition.z};
}

glm::ivec3 getBlockInChunkCoordinates(const ChunkData &chunkData, int x, int y, int z)
{
  return glm::ivec3{
      x - chunkData.worldPosition.x,
      y - chunkData.worldPosition.y,
      z - chunkData.worldPosition.z};
}

MeshData getChunkMeshData(const ChunkData &chunkData)
{
  MeshData meshData(true);

  loopThroughTheBlocks(chunkData, [&](int x, int y, int z)
                       {
        BlockType block = chunkData.blocks[getIndexFromPosition(chunkData, x, y, z)];
        meshData = BlockHelper::getMeshData(chunkData, x, y, z, meshData, block); });

  return meshData;
}

glm::ivec3 chunkPositionFromBlockCoords(const World &world, int x, int y, int z)
{
  return glm::ivec3{
      static_cast<int>(std::floor(x / static_cast<float>(world.chunkSize)) * world.chunkSize),
      static_cast<int>(std::floor(y / static_cast<float>(world.chunkHeight)) * world.chunkHeight),
      static_cast<int>(std::floor(z / static_cast<float>(world.chunkSize)) * world.chunkSize)};
}
