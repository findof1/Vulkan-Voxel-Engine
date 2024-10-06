#ifndef BLOCK_DATA_MANAGER_H
#define BLOCK_DATA_MANAGER_H
#include "blockType.h"
#include "blockDataSO.h"
#include <vector>
#include <unordered_map>
#include <utility>

class BlockDataManager
{
public:
  static float textureOffset;
  static float tileSizeX;
  static float tileSizeY;
  static std::unordered_map<BlockType, TextureData> blockTextureDataDictionary;
  BlockDataSO textureData;

  BlockDataManager(const std::vector<TextureData> &textureDataList, BlockDataSO &&textureData) : textureData(std::move(textureData))
  {

    for (const auto &item : textureDataList)
    {
      if (blockTextureDataDictionary.find(item.blockType) == blockTextureDataDictionary.end())
      {
        blockTextureDataDictionary[item.blockType] = item;
      }
    }
    tileSizeX = textureData.textureSizeX;
    tileSizeY = textureData.textureSizeY;
    textureOffset = 0.001f;
  }
};
#endif