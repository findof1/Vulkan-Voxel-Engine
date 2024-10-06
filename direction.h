
#ifndef DIRECTION_H
#define DIRECTION_H
#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>

enum Direction
{
  foreward,  // z+ direction
  right,     // +x direction
  backwards, // -z direction
  left,      // -x direction
  up,        // +y direction
  down       // -y direction
};

class DirectionExtensions
{
public:
  static glm::ivec3 getVector(Direction direction)
  {
    switch (direction)
    {
    case Direction::up:
      return glm::ivec3(0, 1, 0);
    case Direction::down:
      return glm::ivec3(0, -1, 0);
    case Direction::right:
      return glm::ivec3(1, 0, 0);
    case Direction::left:
      return glm::ivec3(-1, 0, 0);
    case Direction::foreward:
      return glm::ivec3(0, 0, 1);
    case Direction::backwards:
      return glm::ivec3(0, 0, -1);
    default:
      throw std::runtime_error("Invalid input direction");
    }
  }
};
#endif