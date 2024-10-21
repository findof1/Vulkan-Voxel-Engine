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

  int currentCapacity = vertices->capacity();
  int size = meshData->vertices.size() + meshData->waterMesh->vertices.size() + currentCapacity;
  vertices->reserve(size);

  currentCapacity = indices->capacity();
  size = meshData->indices.size() + meshData->waterMesh->indices.size() + currentCapacity;
  indices->reserve(size);

  vertices->insert(vertices->end(), meshData->vertices.begin(), meshData->vertices.end());
  vertices->insert(vertices->end(), meshData->waterMesh->vertices.begin(), meshData->waterMesh->vertices.end());

  indices->insert(indices->end(), meshData->indices.begin(), meshData->indices.end());
  indices->insert(indices->end(), meshData->waterMesh->indices.begin(), meshData->waterMesh->indices.end());
}

void ChunkRenderer::updateChunk(std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{
  MeshData mesh = getChunkMeshData(chunkData, indices->size());
  renderMesh(&mesh, vertices, indices);
}

void ChunkRenderer::updateChunk(MeshData *data, std::vector<Vertex> *vertices, std::vector<uint32_t> *indices)
{
  renderMesh(data, vertices, indices);
}