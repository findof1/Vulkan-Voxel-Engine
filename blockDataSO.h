#ifndef BLOCK_DATA_SO_H
#define BLOCK_DATA_SO_H
#include "blockType.h"
#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class TextureData
{
public:
  BlockType blockType;
  glm::ivec2 up;
  glm::ivec2 down;
  glm::ivec2 side;

  bool isSolid;

  TextureData(BlockType type, glm::ivec2 upPos, glm::ivec2 downPos, glm::ivec2 sidePos)
      : blockType(type), up(upPos), down(downPos), side(sidePos) {}

  TextureData()
  {
  }
};

class BlockDataSO
{
public:
  float textureSizeX, textureSizeY;
  std::vector<TextureData> textureDataList;

  BlockDataSO(float sizeX, float sizeY)
      : textureSizeX(sizeX), textureSizeY(sizeY) {}

  void addTextureData(TextureData textureData)
  {
    textureDataList.push_back(textureData);
  }
};
#endif