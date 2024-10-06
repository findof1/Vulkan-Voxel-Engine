#ifndef WORLD_H
#define WORLD_H
#include "blockType.h"
#include "chunkData.h"
#include "chunkRenderer.h"
#include <map>
#include <glm/glm.hpp>

class World
{
public:
  int mapSizeInChunks = 6;
  int chunkSize = 16, chunkHeight = 100;
  int waterThreshold = 50;
  float noiseScale = 0.03f;

  std::map<glm::ivec3, ChunkData> chunkDataDictionary;
  std::map<glm::ivec3, ChunkRenderer> chunkDictionary;

  World();

  void generateWorld(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);

  void generateVoxels(const ChunkData &data);

  BlockType getBlockFromChunkCoordinates(const ChunkData &chunkData, int x, int y, int z);
};

#endif