#ifndef VOXEL_CONTAINER_HPP_
#define VOXEL_CONTAINER_HPP_

#include <unordered_map>

#include "VoxelGrid.hpp"


namespace IV {
template <typename VoxelGridIndexMapper_, typename ValueType>
class VoxelContainer {
  using VoxelGridIndexMapper = VoxelGridIndexMapper_;
  using Specification = typename VoxelGridIndexMapper::Specification;
  using VoxelTraits = typename Specification::VoxelTraits;
  using VoxelIndex = typename VoxelTraits::Index;

  using PointTraits = typename Specification::PointTraits;
  using Scalar = typename PointTraits::Scalar;

  using Map = std::unordered_map<
                    VoxelIndex,
                    ValueType,
                    typename VoxelIndex::Hasher>;

public:
  using Point = typename PointTraits::Point;
  using iterator = typename Map::iterator;
  using const_iterator = typename Map::const_iterator;

  VoxelContainer() = default;
  explicit VoxelContainer(VoxelGridIndexMapper mapper)
    : mapper(mapper)
  {}

  // {
  ValueType&
  at(Point point)
  { return data.at(mapper.MapPoint(point)); }

  const ValueType&
  at(Point point) const
  { return data.at(mapper.MapPoint(point)); }
  // }

  // {
  ValueType&
  operator[](Point point)
  { return data[mapper.MapPoint(point)]; }

  const ValueType&
  operator[](Point point) const
  { return data[mapper.MapPoint(point)]; }
  // }

  //{
  iterator
  find(Point point)
  { return data.find(mapper.MapPoint(point)); }

  const_iterator
  find(Point point) const
  { return data.find(mapper.MapPoint(point)); }
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
    VoxelGridIndexMapper mapper;
    Map data;
};
} // ns IV

#endif // VOXEL_CONTAINER_HPP_
