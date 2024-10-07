#include "blockHelper.h"
const std::array<Direction, 6> BlockHelper::directions = {foreward,
                                                          right,
                                                          backwards,
                                                          left,
                                                          up,
                                                          down};
MeshData BlockHelper::getMeshData(const ChunkData &chunk, int x, int y, int z, MeshData meshData, BlockType blockType)
{
  if (blockType == BlockType::Air || blockType == BlockType::Nothing)
    return meshData;

  for (const auto &direction : directions)
  {
    glm::ivec3 neighbourBlockCoordinates = glm::ivec3(x, y, z) + getVector(direction);
    BlockType neighbourBlockType = getBlockFromChunkCoordinates(chunk, neighbourBlockCoordinates.x, neighbourBlockCoordinates.y, neighbourBlockCoordinates.z);

    if (neighbourBlockType != BlockType::Nothing)
    {
      if (blockType == BlockType::Water)
      {
        if (neighbourBlockType == BlockType::Air)
        {
          if (neighbourBlockType == BlockType::Air)
            meshData.waterMesh = std::make_unique<MeshData>(getFaceDataIn(direction, chunk, x, y, z, *meshData.waterMesh, blockType));
        }
      }
      else
      {
        meshData = getFaceDataIn(direction, chunk, x, y, z, meshData, blockType);
      }
    }
  }

  return meshData;
}

MeshData BlockHelper::getFaceDataIn(Direction direction, const ChunkData &chunk, int x, int y, int z, MeshData meshData, BlockType blockType)
{
  GetFaceVertices(direction, x, y, z, meshData, blockType);
  meshData.addIndices();

  return meshData;
}

void BlockHelper::GetFaceVertices(Direction direction, int x, int y, int z, MeshData &meshData, BlockType blockType)
{

  switch (direction)
  {
  case Direction::backwards:
    meshData.addVertex(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), faceUVs(direction, blockType));
    break;
  case Direction::foreward:
    meshData.addVertex(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), faceUVs(direction, blockType));
    break;
  case Direction::left:
    meshData.addVertex(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), faceUVs(direction, blockType));
    break;
  case Direction::right:
    meshData.addVertex(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), faceUVs(direction, blockType));
    break;
  case Direction::down:
    meshData.addVertex(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), faceUVs(direction, blockType));
    break;
  case Direction::up:
    meshData.addVertex(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), faceUVs(direction, blockType));
    meshData.addVertex(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), faceUVs(direction, blockType));
    break;
  default:
    break;
  }
}

std::array<glm::vec2, 4> BlockHelper::faceUVs(Direction direction, BlockType blockType)
{
  std::array<glm::vec2, 4> UVs;
  auto tilePos = TexturePosition(direction, blockType);

  UVs[0] = glm::vec2(BlockDataManager::tileSizeX * tilePos.x + BlockDataManager::tileSizeX - BlockDataManager::textureOffset,
                     BlockDataManager::tileSizeY * tilePos.y + BlockDataManager::textureOffset);

  UVs[1] = glm::vec2(BlockDataManager::tileSizeX * tilePos.x + BlockDataManager::tileSizeX - BlockDataManager::textureOffset,
                     BlockDataManager::tileSizeY * tilePos.y + BlockDataManager::tileSizeY - BlockDataManager::textureOffset);

  UVs[2] = glm::vec2(BlockDataManager::tileSizeX * tilePos.x + BlockDataManager::textureOffset,
                     BlockDataManager::tileSizeY * tilePos.y + BlockDataManager::tileSizeY - BlockDataManager::textureOffset);

  UVs[3] = glm::vec2(BlockDataManager::tileSizeX * tilePos.x + BlockDataManager::textureOffset,
                     BlockDataManager::tileSizeY * tilePos.y + BlockDataManager::textureOffset);

  return UVs;
}

glm::ivec3 BlockHelper::getVector(Direction direction)
{
  switch (direction)
  {
  case Direction::backwards:
    return glm::ivec3(0, 0, -1);
  case Direction::down:
    return glm::ivec3(0, -1, 0);
  case Direction::foreward:
    return glm::ivec3(0, 0, 1);
  case Direction::left:
    return glm::ivec3(-1, 0, 0);
  case Direction::right:
    return glm::ivec3(1, 0, 0);
  case Direction::up:
    return glm::ivec3(0, 1, 0);
  default:
    throw std::invalid_argument("Invalid direction");
  }
}

glm::ivec2 BlockHelper::TexturePosition(Direction direction, BlockType blockType)
{
  switch (direction)
  {
  case Direction::up:
    return BlockDataManager::blockTextureDataDictionary[blockType].up;
  case Direction::down:
    return BlockDataManager::blockTextureDataDictionary[blockType].down;
  default:
    return BlockDataManager::blockTextureDataDictionary[blockType].side;
  }
}