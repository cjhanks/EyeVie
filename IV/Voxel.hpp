#ifndef VOXEL_HPP_
#define VOXEL_HPP_

#include <cstring>
#include <cstdint>

#include <glog/logging.h>

#include "detail/Voxel.hpp"


namespace IV {
/// {
/// @class VoxelIndex
/// An indexer appropriate for use in an unordered map.
///
/// @tparam MaxSizeI of 100 (for example) would imply a range of I
///         from -100 to +100.
/// @tparam MaxSizeJ @see MaxSizeI
/// @tparam MaxSizeK @see MaxSizeI
template <
  std::size_t MaxSizeI_,
  std::size_t MaxSizeJ_,
  std::size_t MaxSizeK_
>
struct VoxelIndex {
  /// {
  static constexpr std::int64_t MaxSizeI = +MaxSizeI_;
  static constexpr std::int64_t MinSizeI = -MaxSizeI_;

  static constexpr std::int64_t MaxSizeJ = +MaxSizeJ_;
  static constexpr std::int64_t MinSizeJ = -MaxSizeJ_;

  static constexpr std::int64_t MaxSizeK = +MaxSizeK_;
  static constexpr std::int64_t MinSizeK = -MaxSizeK_;
  /// }

  /// {
  static constexpr
  std::size_t BitsI = detail::BitsRequired<2 * MaxSizeI>::value;

  static constexpr
  std::size_t BitsJ = detail::BitsRequired<2 * MaxSizeJ>::value;

  static constexpr
  std::size_t BitsK = detail::BitsRequired<2 * MaxSizeK>::value;
  /// }

  using IndexType = typename detail::TypeFor<BitsI + BitsJ + BitsK>::type;

  /// {
  static constexpr
  std::size_t BitsUndefined = detail::BitsUndefined<
                                        IndexType,
                                        BitsI,
                                        BitsJ,
                                        BitsK>::value;
  using IJK_Bits = ::IV::detail::IJK_Bits<BitsI, BitsJ, BitsK, BitsUndefined>;
  /// }

  // {
  // Implicit types inherited by users
  struct Hasher {
    inline std::size_t
    operator()(const VoxelIndex& index) const {
      return index.id;
    }
  };
  // }

  // {
  // Useful methods
  template <typename Int>
  VoxelIndex(Int i, Int j, Int k)
    : ijk(i, j, k)
  {
    DCHECK(ijk.i == i) << "(over/under)flow X";
    DCHECK(ijk.j == j) << "(over/under)flow Y";
    DCHECK(ijk.k == k) << "(over/under)flow Z";
  }

  explicit VoxelIndex(IndexType id)
    : id(id)
  {}

  bool
  operator==(const VoxelIndex& rhs) const {
    return id == rhs.id;
  }
  // }

  // { Data elements
  union {
    IJK_Bits ijk;
    IndexType id;
  };
  // }
};
/// }
} // ns IV

#endif // VOXEL_HPP_
