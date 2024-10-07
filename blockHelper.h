#ifndef BLOCK_HELPER_H
#define BLOCK_HELPER_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <array>
#include "chunkData.h"
#include "direction.h"
#include "meshData.h"
#include "blockDataManager.h"
#include "chunkUtils.h"

class ChunkData;

class BlockHelper
{
private:
  static const std::array<Direction, 6> directions;

public:
  static MeshData getMeshData(const ChunkData &chunk, int x, int y, int z, MeshData meshData, BlockType blockType);

  static MeshData getFaceDataIn(Direction direction, const ChunkData &chunk, int x, int y, int z, MeshData meshData, BlockType blockType);

  static void GetFaceVertices(Direction direction, int x, int y, int z, MeshData &meshData, BlockType blockType);

  static std::array<glm::vec2, 4> faceUVs(Direction direction, BlockType blockType);

private:
  static glm::ivec3 getVector(Direction direction);

  static glm::ivec2 TexturePosition(Direction direction, BlockType blockType);
};

#endif