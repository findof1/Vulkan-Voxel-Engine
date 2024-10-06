#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "chunkData.h"
#include "chunkUtils.h"
#include "chunkRenderer.h"

ChunkRenderer::ChunkRenderer(const ChunkData &data) : chunkData(data)
{
}

ChunkRenderer::ChunkRenderer(ChunkData &&data) : chunkData(std::move(data))
{
}

void ChunkRenderer::renderMesh(MeshData meshData, std::vector<Vertex> &vertices, std::vector<uint32_t> &indices)
{
  vertices.reserve(meshData.vertices.size() + meshData.waterMesh->vertices.size());
  vertices.insert(vertices.end(), meshData.vertices.begin(), meshData.vertices.end());
  vertices.insert(vertices.end(), meshData.waterMesh->vertices.begin(), meshData.waterMesh->vertices.end());

  indices.reserve(meshData.indices.size() + meshData.waterMesh->indices.size());
  indices.insert(indices.end(), meshData.indices.begin(), meshData.indices.end());
  indices.insert(indices.end(), meshData.waterMesh->indices.begin(), meshData.waterMesh->indices.end());
}

void ChunkRenderer::updateChunk(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices)
{
  renderMesh(getChunkMeshData(chunkData), vertices, indices);
}

void ChunkRenderer::updateChunk(MeshData data, std::vector<Vertex> &vertices, std::vector<uint32_t> &indices)
{
  renderMesh(data, vertices, indices);
}