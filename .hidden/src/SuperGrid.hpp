#ifndef SUPER_GRID_HPP_
#define SUPER_GRID_HPP_

#include <cassert>

#include "detail/SuperGrid.hpp"
#include "Voxel.hpp"


namespace IV {
template <
  typename VoxelGrid,
  typename VoxelData = detail::EmptyDataStruct
  >
class SuperGrid {
public:
  using Point = typename VoxelGrid::Point;
  using VoxelNeighborhood =
          typename detail::VoxelNeighborhood<VoxelGrid>;

  struct Settings {
    std::size_t superSampleX = 0;
    std::size_t superSampleY = 0;
    std::size_t superSampleZ = 0;
  };

  SuperGrid(Settings settings, VoxelGrid& voxelGrid)
    : settings(settings)
    , voxelGrid(voxelGrid)
  {
    assert(settings.superSampleX > 0);
    assert(settings.superSampleY > 0);
    assert(settings.superSampleZ > 0);
  }

  SuperGrid(Settings settings_, SuperGrid& superGrid)
    : settings(settings_)
    , voxelGrid(superGrid.voxelGrid)
  {
    settings.superSampleX =
             superGrid.superSampleX * settings_.superSampleX;
    settings.superSampleY =
             superGrid.superSampleY * settings_.superSampleY;
    settings.superSampleZ =
             superGrid.superSampleZ * settings_.superSampleZ;
  }

  VoxelNeighborhood
  at(Point origin)
  {
    return at(origin, 0);
  }

  VoxelNeighborhood
  at(Point origin, std::size_t size)
  {
    auto index = voxelGrid.MapPoint(origin);
    return VoxelNeighborhood(voxelGrid, index, size);
  }

private:
  const Settings settings;
  VoxelGrid& voxelGrid;
};
} // ns IV

#endif // SUPER_GRID_HPP_
