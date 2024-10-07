#include "blockDataManager.h"
float BlockDataManager::textureOffset = 0;
float BlockDataManager::tileSizeX = 0;
float BlockDataManager::tileSizeY = 0;
std::unordered_map<BlockType, TextureData> BlockDataManager::blockTextureDataDictionary;

BlockDataManager::BlockDataManager(const std::vector<TextureData> &textureDataList, BlockDataSO &&textureData) : textureData(std::move(textureData))
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
