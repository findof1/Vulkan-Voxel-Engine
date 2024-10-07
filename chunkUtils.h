
#ifndef CHUNK_UTILS_H
#define CHUNK_UTILS_H
#include <vector>
#include <functional>
#include <stdexcept>
#include <glm/glm.hpp>
#include "chunkData.h"
#include "blockType.h"
#include "meshData.h"
#include "blockHelper.h"

class ChunkData;
class World;

glm::ivec3 getPositionFromIndex(const ChunkData &chunkData, int index);

void loopThroughTheBlocks(const ChunkData &chunkData, std::function<void(int, int, int)> actionToPerform);

bool inRange(const ChunkData &chunkData, int axisCoordinate);

bool inRangeHeight(const ChunkData &chunkData, int ycoordinate);

BlockType getBlockFromChunkCoordinates(const ChunkData &chunkData, glm::ivec3 chunkCoordinates);

BlockType getBlockFromChunkCoordinates(const ChunkData &chunkData, int x, int y, int z);

void setBlock(ChunkData &chunkData, const glm::ivec3 &localPosition, BlockType block);

int getIndexFromPosition(const ChunkData &chunkData, int x, int y, int z);

glm::ivec3 getBlockInChunkCoordinates(const ChunkData &chunkData, const glm::ivec3 &pos);

glm::ivec3 getBlockInChunkCoordinates(const ChunkData &chunkData, int x, int y, int z);

MeshData getChunkMeshData(const ChunkData &chunkData);

glm::ivec3 chunkPositionFromBlockCoords(World *world, int x, int y, int z);

#endif