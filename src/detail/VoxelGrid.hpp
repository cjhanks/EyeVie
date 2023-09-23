#ifndef DETAIL_VOXEL_GRID_HPP_
#define DETAIL_VOXEL_GRID_HPP_

#include <cstdint>
#include <cstring>

#include "ByteManipulation.hpp"


namespace IV { namespace detail {
template <typename Specification_>
struct VoxelDataPoint {
  using Specification = Specification_;
  using Data = typename Specification::Data;
  static constexpr std::size_t BitsPerIndex =
          Specification::BitsPerPointIndex;
  static constexpr std::size_t Scaler = (1 << BitsPerIndex);
  using IndexType = typename detail::TypeFor<3 * BitsPerIndex>;

  VoxelDataPoint(
      unsigned deltaI,
      unsigned deltaJ,
      unsigned deltaK,
      Data data)
    : deltaI(deltaI)
    , deltaJ(deltaJ)
    , deltaK(deltaK)
    , data(data)
  {}

  union {
    struct {
      unsigned deltaI:BitsPerIndex;
      unsigned deltaJ:BitsPerIndex;
      unsigned deltaK:BitsPerIndex;
    } __attribute__((packed));

    IndexType point;
  };

  Data data;
};

template <typename Specification_>
struct VoxelData {
  using Specification = Specification_;
  using DataPoint = VoxelDataPoint<Specification>;
  using PointVector = std::vector<DataPoint>;

  PointVector points;
};
} // ns detail
} // ns IV

#endif // DETAIL_VOXEL_GRID_HPP_
