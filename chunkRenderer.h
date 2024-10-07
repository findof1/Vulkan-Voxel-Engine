
#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <vector>
#include "chunkData.h"

class ChunkData;
class MeshData;

class ChunkRenderer
{
public:
  ChunkData *chunkData;

  ChunkRenderer();

  ChunkRenderer(ChunkData &data);

  ChunkRenderer(ChunkData &&data);

  void renderMesh(MeshData meshData, std::vector<Vertex> *vertices, std::vector<uint32_t> *indices);

  void updateChunk(std::vector<Vertex> *vertices, std::vector<uint32_t> *indices);

  void updateChunk(MeshData data, std::vector<Vertex> *vertices, std::vector<uint32_t> *indices);
};

#endif