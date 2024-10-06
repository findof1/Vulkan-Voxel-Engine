
#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "chunkData.h"
#include "chunkUtils.h"

class ChunkRenderer
{
public:
  ChunkData chunkData;

  ChunkRenderer(const ChunkData &data);

  ChunkRenderer(ChunkData &&data);

  void renderMesh(MeshData meshData, std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);

  void updateChunk(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);

  void updateChunk(MeshData data, std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);
};

#endif