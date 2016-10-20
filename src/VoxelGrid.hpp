#ifndef VOXEL_GRID_HPP_
#define VOXEL_GRID_HPP_

#include <cstdint>
#include <cmath>
#include <unordered_map>
#include <vector>

#include "detail/VoxelGrid.hpp"

#include "Voxel.hpp"
#include "VoxelQuery.hpp"

#include <iostream>


namespace IV {
/// {
template <
  typename Point_,
  std::size_t XWidth,
  std::size_t YWidth,
  std::size_t ZWidth
>
struct VoxelSpecifications {
  using Point = Point_;
  using Scalar = double; // TODO: Derive from Point::x,y,z
  using Data = decltype(((Point*)(nullptr))->data);

  static constexpr std::size_t DepthI = XWidth;
  static constexpr std::size_t DepthJ = YWidth;
  static constexpr std::size_t DepthK = ZWidth;

  static constexpr std::size_t BitsPerPointIndex = 5;
};
/// }


template <typename Specification_>
class VoxelGrid {
public:
  using SelfType = VoxelGrid<Specification_>;
  using Specification = Specification_;
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


  struct PointElement {
    Scalar x;
    Scalar y;
    Scalar z;
    VoxelData* data = nullptr;
  };

  explicit VoxelGrid(Specification specification)
    : specification(specification)
  {}

  void
  AddPoint(Point point)
  {
    auto index = MapPoint(point);
    data[index].points.emplace_back(
                        PointGlobalToPointLocal(index, point));
  }

  PointAccessor
  at(VoxelIndex index)
  {
    auto elem = data.find(index);
    if (elem == data.end())
      return PointAccessor();
    else
      return PointAccessor(index, &elem->second);
  }

  VoxelNeighborhood
  at(VoxelIndex index, std::size_t size)
  {
    return VoxelNeighborhood(*this, size);
  }

  VoxelIndex
  MapPoint(Point point) const
  {
    return MapPoint(point.x, point.y, point.z);
  }

  VoxelIndex
  MapPoint(Scalar x, Scalar y, Scalar z) const
  {
    return MapPointImpl(x, y, z);
  }

protected:
  const Specification specification;
  std::unordered_map<
        VoxelIndex,
        VoxelData,
        typename VoxelIndex::Hasher> data;

  VoxelIndex
  MapPointImpl(Scalar x, Scalar y, Scalar z) const
  {
    auto indexI = std::floor(x);
    auto indexJ = std::floor(y);
    auto indexK = std::floor(z);

    return VoxelIndex(indexI, indexJ, indexK);
  }

  static VoxelDataPoint
  PointGlobalToPointLocal(const VoxelIndex& index, Point point)
  {
    assert(point.x >= index.i);
    assert(point.y >= index.j);
    assert(point.z >= index.k);

    point.x -= index.i;
    point.y -= index.j;
    point.z -= index.k;

    assert(point.x <= 1 && point.x >= 0);
    assert(point.y <= 1 && point.y >= 0);
    assert(point.z <= 1 && point.z >= 0);

    return VoxelDataPoint(std::round(point.x * VoxelDataPoint::Scaler),
                          std::round(point.y * VoxelDataPoint::Scaler),
                          std::round(point.z * VoxelDataPoint::Scaler),
                          point.data);
  }

  static PointElement
  PointLocalToPointGlobal(const VoxelIndex& index, const VoxelDataPoint& point)
  {
    Point pt;
    pt.x = index.i + (double(point.deltaI) / VoxelDataPoint::Scaler);
    pt.y = index.j + (double(point.deltaJ) / VoxelDataPoint::Scaler);
    pt.z = index.k + (double(point.deltaK) / VoxelDataPoint::Scaler);
    pt.data = &(point.data);

    return pt;
  }
};
} // ns IV

#endif // VOXEL_GRID_HPP_
