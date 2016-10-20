#ifndef VOXEL_CONTAINER_HPP_
#define VOXEL_CONTAINER_HPP_

#include <unordered_map>

#include "VoxelGrid.hpp"


namespace IV {
template <typename VoxelGrid, typename ValueType>
class VoxelContainer : public VoxelGrid {
public:
  using Specification = typename VoxelGrid::Specification;
  using SelfType = VoxelContainer<VoxelGrid, ValueType>;
  using Point = typename Specification::Point;
  using VoxelIndex = detail::VoxelIndex<Specification::DepthI,
                                        Specification::DepthJ,
                                        Specification::DepthK>;
  using Scalar = typename Specification::Scalar;
  using VoxelData = detail::VoxelData<Specification>;
  using VoxelDataPoint = typename VoxelData::DataPoint;
  using PointVector = typename VoxelData::PointVector;
  using PointAccessor = detail::PointAccessor<SelfType>;
  using VoxelNeighborhood = detail::VoxelNeighborhood<SelfType>;

private:
  using Map = std::unordered_map<
                    VoxelIndex,
                    ValueType,
                    typename VoxelIndex::Hasher>;

public:
  using iterator = typename Map::iterator;
  using const_iterator = typename Map::const_iterator;

  using VoxelGrid::VoxelGrid;

  // {
  ValueType&
  at(Point point)
  { return data.at(MapPoint(point)); }

  const ValueType&
  at(Point point) const
  { return data.at(MapPoint(point)); }
  // }

  // {
  ValueType&
  operator[](Point point)
  { return data[MapPoint(point)]; }

  const ValueType&
  operator[](Point point) const
  { return data[MapPoint(point)]; }
  // }

  //{
  iterator
  find(Point point)
  { return data.find(MapPoint(point)); }

  const_iterator
  find(Point point) const
  { return data.find(MapPoint(point)); }
  //}

  // {
  iterator
  begin()
  { return data.begin(); }

  iterator
  end()
  { return data.end(); }

  const_iterator
  begin() const
  { return data.begin(); }

  const_iterator
  end() const
  { return data.end(); }
  // }

 private:
    Map data;
};
} // ns IV

#endif // VOXEL_CONTAINER_HPP_
