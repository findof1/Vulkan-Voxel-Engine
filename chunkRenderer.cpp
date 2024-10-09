#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "chunkData.h"
#include "chunkUtils.h"
#include "chunkRenderer.h"

ChunkRenderer::ChunkRenderer() : chunkData(new ChunkData(nullptr, glm::vec3(0), 0, 0))
{
}

ChunkRenderer::ChunkRenderer(ChunkData *data) : chunkData(data)
{
}

void ChunkRenderer::renderMesh(MeshData *meshData, std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{

  int size = meshData->vertices.size() + meshData->waterMesh->vertices.size();
  vertices->reserve(size);

  size = meshData->indices.size() + meshData->waterMesh->indices.size();
  indices->reserve(size);

  std::cin.get();
  vertices->insert(vertices->end(), meshData->vertices.begin(), meshData->vertices.end());
  vertices->insert(vertices->end(), meshData->waterMesh->vertices.begin(), meshData->waterMesh->vertices.end());

  indices->insert(indices->end(), meshData->indices.begin(), meshData->indices.end());
  indices->insert(indices->end(), meshData->waterMesh->indices.begin(), meshData->waterMesh->indices.end());
}

void ChunkRenderer::updateChunk(std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{
  MeshData mesh = getChunkMeshData(chunkData);
  renderMesh(&mesh, vertices, indices);
}

void ChunkRenderer::updateChunk(MeshData *data, std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{
  renderMesh(data, vertices, indices);
}