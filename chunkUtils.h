
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

glm::ivec3 getPositionFromIndex(ChunkData *chunkData, int index);

void loopThroughTheBlocks(ChunkData *chunkData, std::function<void(int, int, int)> actionToPerform);

bool inRange(ChunkData *chunkData, int axisCoordinate);

bool inRangeHeight(ChunkData *chunkData, int ycoordinate);

BlockType getBlockFromChunkCoordinates(ChunkData *chunkData, glm::ivec3 chunkCoordinates);

BlockType getBlockFromChunkCoordinates(ChunkData *chunkData, int x, int y, int z);

void setBlock(ChunkData *chunkData, const glm::ivec3 &localPosition, BlockType block);

int getIndexFromPosition(ChunkData *chunkData, int x, int y, int z);

glm::ivec3 getBlockInChunkCoordinates(ChunkData *chunkData, const glm::ivec3 &pos);

glm::ivec3 getBlockInChunkCoordinates(ChunkData *chunkData, int x, int y, int z);

MeshData getChunkMeshData(ChunkData *chunkData);

glm::ivec3 chunkPositionFromBlockCoords(World *world, int x, int y, int z);

#endif