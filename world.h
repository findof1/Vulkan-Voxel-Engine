#ifndef WORLD_H
#define WORLD_H
#include "blockType.h"
#include "chunkData.h"
#include "vertex.h"
#include "chunkRenderer.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>

class ChunkData;

struct Vec3Comparator
{
  bool operator()(const glm::ivec3 &a, const glm::ivec3 &b) const
  {
    if (a.x != b.x)
      return a.x < b.x;
    if (a.y != b.y)
      return a.y < b.y;
    return a.z < b.z;
  }
};

class World
{
public:
  int mapSizeInChunks = 10;
  int chunkSize = 16, chunkHeight = 100;
  int waterThreshold = 50;
  float noiseScale = 0.006f;

  std::map<glm::ivec3, ChunkData, Vec3Comparator> chunkDataDictionary;
  std::map<glm::ivec3, ChunkRenderer, Vec3Comparator> chunkDictionary;

  World();

  void generateWorld(std::vector<Vertex> *vertices, std::vector<uint32_t> *indices);

  void generateVoxels(ChunkData *data);

  BlockType getBlockFromChunkCoordinates(ChunkData *chunkData, int x, int y, int z, int depth);
};

#endif