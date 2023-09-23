#ifndef VOXEL_GRID_HPP_
#define VOXEL_GRID_HPP_

#include <stdexcept>
#include <type_traits>

#include "Voxel.hpp"


namespace IV {
template <typename Point_>
struct PointTraits {
  using Point = Point_;
  using Scalar = decltype(((Point*)(nullptr))->x);

  static_assert(
      std::is_same<decltype(((Point*)(nullptr))->x),
                   decltype(((Point*)(nullptr))->y)>::value
   && std::is_same<decltype(((Point*)(nullptr))->y),
                   decltype(((Point*)(nullptr))->z)>::value,
    "Mismatched types for point XYZ");
};

template <
  std::size_t XWidth,
  std::size_t YWidth,
  std::size_t ZWidth
  >
struct VoxelTraits {
  static constexpr std::size_t DepthI = XWidth;
  static constexpr std::size_t DepthJ = YWidth;
  static constexpr std::size_t DepthK = ZWidth;

  using Index = detail::VoxelIndex<DepthI, DepthJ, DepthK>;
};


/// @class VoxelSpecifications
template <
  typename Point_,
  std::size_t XWidth,
  std::size_t YWidth,
  std::size_t ZWidth
>
struct VoxelSpecifications {
  using PointTraits = IV::PointTraits<Point_>;
  using VoxelTraits = IV::VoxelTraits<XWidth, YWidth, ZWidth>;

  // {
  // Begin user overloadable types
  static constexpr std::size_t BitsPerPointIndex = 5;
  // }
};

////////////////////////////////////////////////////////////////////////////////

/// @class VoxelGridIndexMapper
///
///
template <typename Specification_>
class VoxelGridIndexMapper {
public:
  using Specification = Specification_;
  using PointTraits = typename Specification::PointTraits;
  using Scalar = typename PointTraits::Scalar;
  using Point = typename PointTraits::Point;

  using VoxelTraits = typename Specification::VoxelTraits;
  using VoxelIndex = typename VoxelTraits::Index;

  // {
  // Maps a point to a specific voxel index. If the requested point would
  // overflow an `out_of_range` error is thrown when NDEBUG is not defined.
  // If NDEBUG is defined, overflow behavior is undefined.
  inline VoxelIndex
  MapPoint(Point point) const
  { return MapPoint(point.x, point.y, point.z); }

  inline VoxelIndex
  MapPoint(Scalar x, Scalar y, Scalar z) const
  { return MapPointImpl(x, y, z); }
  // }

private:
  inline VoxelIndex
  MapPointImpl(Scalar x, Scalar y, Scalar z) const
  {
    auto indexI = std::floor(x);
    auto indexJ = std::floor(y);
    auto indexK = std::floor(z);

#if !defined(NDEBUG)
    if (std::abs(indexI) > VoxelTraits::DepthI
     || std::abs(indexJ) > VoxelTraits::DepthJ
     || std::abs(indexK) > VoxelTraits::DepthK
     ) {
      throw std::out_of_range("Mapped point would overflow.");
    }
#endif

    return VoxelIndex(indexI, indexJ, indexK);
  }
};
} // ns IV

#endif // VOXEL_GRID_HPP_
