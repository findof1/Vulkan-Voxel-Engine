
#ifndef MESH_DATA_H
#define MESH_DATA_H
#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"

class MeshData
{
public:
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
  MeshData *waterMesh;

  MeshData(bool isMainMesh = true) : isMainMesh(isMainMesh)
  {
    if (isMainMesh)
    {
      waterMesh = new MeshData(false);
    }
  }

  MeshData(const MeshData &other)
      : vertices(other.vertices),
        indices(other.indices)
  {
  }

  MeshData(MeshData &&other) noexcept
      : vertices(std::move(other.vertices)),
        indices(std::move(other.indices))
  {
    other.vertices.clear();
    other.indices.clear();
  }

  MeshData &operator=(MeshData &&other) noexcept
  {
    if (this != &other)
    {
      vertices = std::move(other.vertices);
      indices = std::move(other.indices);
      other.vertices.clear();
      other.indices.clear();
    }
    return *this;
  }

  void addVertex(glm::vec3 position, std::array<glm::vec2, 4UL> faceUVs)
  {
    for (int i = 0; i < 4; ++i)
    {
      Vertex vertex;
      vertex.pos = position;
      vertex.color = glm::vec3(1.0f, 1.0f, 1.0f);
      vertex.texPos = faceUVs[i];

      vertices.push_back(vertex);
    }
  }

  void addIndices()
  {
    indices.emplace_back(vertices.size() - 4);
    indices.emplace_back(vertices.size() - 2);
    indices.emplace_back(vertices.size() - 3);

    indices.emplace_back(vertices.size() - 4);
    indices.emplace_back(vertices.size() - 1);
    indices.emplace_back(vertices.size() - 2);
  }

private:
  bool isMainMesh = true;
};
#endif