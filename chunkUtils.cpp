
#include <vector>
#include <functional>
#include <stdexcept>
#include <glm/glm.hpp>
#include "chunkData.h"
#include "blockType.h"
#include "meshData.h"
#include "blockHelper.h"

glm::ivec3 getPositionFromIndex(ChunkData *chunkData, int index)
{
  int x = index % chunkData->chunkSize;
  int y = (index / chunkData->chunkSize) % chunkData->chunkHeight;
  int z = index / (chunkData->chunkSize * chunkData->chunkHeight);
  return {x, y, z};
}

void loopThroughTheBlocks(ChunkData *chunkData, std::function<void(int, int, int)> actionToPerform)
{
  for (int x = 0; x < chunkData->chunkSize; x++)
  {
    for (int z = 0; z < chunkData->chunkSize; z++)
    {
      for (int y = 0; y < chunkData->chunkHeight; y++)
      {
        actionToPerform(x, y, z);
      }
    }
  }
}

bool inRange(ChunkData *chunkData, int axisCoordinate)
{
  return axisCoordinate >= 0 && axisCoordinate < chunkData->chunkSize;
}

bool inRangeHeight(ChunkData *chunkData, int ycoordinate)
{
  return ycoordinate >= 0 && ycoordinate < chunkData->chunkHeight;
}

BlockType getBlockFromChunkCoordinates(ChunkData *chunkData, glm::ivec3 chunkCoordinates)
{
  return getBlockFromChunkCoordinates(chunkData, chunkCoordinates.x, chunkCoordinates.y, chunkCoordinates.z);
}

BlockType getBlockFromChunkCoordinates(ChunkData *chunkData, int x, int y, int z)
{
  if (inRange(chunkData, x) && inRangeHeight(chunkData, y) && inRange(chunkData, z))
  {
    int index = getIndexFromPosition(chunkData, x, y, z);
    return chunkData->blocks[index];
  }

  return chunkData->world->getBlockFromChunkCoordinates(chunkData, chunkData->worldPosition.x + x, chunkData->worldPosition.y + y, chunkData->worldPosition.z + z, 0);
}

void setBlock(ChunkData *chunkData, const glm::ivec3 &localPosition, BlockType block)
{
  if (inRange(chunkData, localPosition.x) && inRangeHeight(chunkData, localPosition.y) && inRange(chunkData, localPosition.z))
  {
    int index = getIndexFromPosition(chunkData, localPosition.x, localPosition.y, localPosition.z);
    chunkData->blocks[index] = block;
  }
  else
  {
    throw std::runtime_error("Need to ask World for appropriate chunk");
  }
}

int getIndexFromPosition(ChunkData *chunkData, int x, int y, int z)
{
  return x + chunkData->chunkSize * (z + chunkData->chunkSize * y);
}

glm::ivec3 getBlockInChunkCoordinates(ChunkData *chunkData, const glm::ivec3 &pos)
{
  return glm::ivec3{
      pos.x - chunkData->worldPosition.x,
      pos.y - chunkData->worldPosition.y,
      pos.z - chunkData->worldPosition.z};
}

glm::ivec3 getBlockInChunkCoordinates(ChunkData *chunkData, int x, int y, int z)
{
  return glm::ivec3{
      x - chunkData->worldPosition.x,
      y - chunkData->worldPosition.y,
      z - chunkData->worldPosition.z};
}

MeshData getChunkMeshData(ChunkData *chunkData)
{

  MeshData meshData(true);

  int chunkSize = chunkData->chunkSize;
  int chunkHeight = chunkData->chunkHeight;

  ChunkData copiedData = *chunkData;

  for (int z = 0; z < chunkSize; z++)
  {
    for (int y = 0; y < chunkHeight; y++)
    {
      int preCalculation = chunkData->chunkSize * (z + chunkData->chunkSize * y);

      for (int x = 0; x < chunkSize; x++)
      {

        int index = x + preCalculation;
        BlockType block = copiedData.blocks[index];

        BlockHelper::getMeshData(chunkData, x, y, z, &meshData, block);
      }
    }
  }
  return meshData;
}

glm::ivec3 chunkPositionFromBlockCoords(World *world, int x, int y, int z)
{
  return glm::ivec3{
      static_cast<int>(std::floor(x / static_cast<float>(world->chunkSize)) * world->chunkSize),
      static_cast<int>(std::floor(y / static_cast<float>(world->chunkHeight)) * world->chunkHeight),
      static_cast<int>(std::floor(z / static_cast<float>(world->chunkSize)) * world->chunkSize)};
}
