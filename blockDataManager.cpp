#include "blockDataManager.h"
float BlockDataManager::textureOffset = 0.001;
float BlockDataManager::tileSizeX = 0;
float BlockDataManager::tileSizeY = 0;
std::unordered_map<BlockType, TextureData> BlockDataManager::blockTextureDataDictionary;

BlockDataManager::BlockDataManager(BlockDataSO *textureData) : textureData(textureData)
{
  for (const auto &item : textureData->textureDataList)
  {
    if (blockTextureDataDictionary.find(item.blockType) == blockTextureDataDictionary.end())
    {
      blockTextureDataDictionary[item.blockType] = item;
    }
  }
  tileSizeX = textureData->textureSizeX;
  tileSizeY = textureData->textureSizeY;
}
