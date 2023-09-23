#ifndef IV_VOXEL_GRID_HPP_
#define IV_VOXEL_GRID_HPP_

#include <unordered_map>

#include "Specification.hpp"
#include "Voxel.hpp"


namespace IV {
template <typename Specification_>
class VoxelGrid {
public:
  using Specification = Specification_;
  using Point = typename Specification::Point;
  using PointData = typename Specification::PointData;
  using VoxelIndex = IV::VoxelIndex<
                          Specification::MaxUnitsX,
                          Specification::MaxUnitsY,
                          Specification::MaxUnitsZ
                      >;

private:
  using Map = std::unordered_map<VoxelIndex, PointData>;

public:
  using iterator = typename Map::iterator;
  using const_iterator = typename Map::const_iterator;


private:
  Map data;
};

} // ns IV

#endif // IV_VOXEL_GRID_HPP_
