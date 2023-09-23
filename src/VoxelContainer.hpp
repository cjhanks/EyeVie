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
  { return data.at(this->MapPoint(point)); }

  const ValueType&
  at(Point point) const
  { return data.at(this->MapPoint(point)); }
  // }

  // {
  ValueType&
  operator[](Point point)
  { return data[this->MapPoint(point)]; }

  const ValueType&
  operator[](Point point) const
  { return data[this->MapPoint(point)]; }
  // }

  //{
  iterator
  find(Point point)
  { return data.find(this->MapPoint(point)); }

  const_iterator
  find(Point point) const
  { return data.find(this->MapPoint(point)); }
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

  // {
  size_t
  Size() const
  { return data.size(); }

  size_t
  size() const
  { return data.size(); }
  // }

  template <typename Predicate>
  void
  Filter(Predicate predicate)
  {
    for (auto iter = begin(); iter != end(); /**/) {
      if (predicate(iter->second))
        iter = data.erase(iter);
      else
        ++iter;
    }
  }

 private:
    Map data;
};
} // ns IV

#endif // VOXEL_CONTAINER_HPP_
