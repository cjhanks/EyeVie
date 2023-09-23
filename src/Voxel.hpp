#ifndef VOXEL_HPP_
#define VOXEL_HPP_

#include <cstring>
#include <cstdint>

#include "ByteManipulation.hpp"


namespace IV { namespace detail {
/// {
/// @class VoxelIndex
/// An indexer appropriate for use in an unordered map.
template <
  std::size_t MaxSizeI,
  std::size_t MaxSizeJ,
  std::size_t MaxSizeK
>
struct VoxelIndex {
  static constexpr
  std::size_t BitsI = detail::BitsRequired<2 * MaxSizeI>::value;

  static constexpr
  std::size_t BitsJ = detail::BitsRequired<2 * MaxSizeJ>::value;

  static constexpr
  std::size_t BitsK = detail::BitsRequired<2 * MaxSizeK>::value;

  using IndexType = typename detail::TypeFor<BitsI + BitsJ + BitsK>::type;

  // {
  // Implicit types inherited by users
  struct Hasher {
    std::size_t
    operator()(const VoxelIndex& index) const {
      return index.id;
    }
  };
  // }

  // {
  // Useful methods
  VoxelIndex(long i, long j, long k)
    : i(i)
    , j(j)
    , k(k)
  {}

  VoxelIndex(IndexType id)
    : id(id)
  {}

  bool
  operator==(const VoxelIndex& rhs) const {
    return id == rhs.id;
  }
  // }

  // { Data elements
  union {
    struct {
      long i:BitsI;
      long j:BitsJ;
      long k:BitsK;
    } __attribute__((packed));

   IndexType id;
  };
  // }
};
/// }
} // ns detail
} // ns IV

#endif // VOXEL_HPP_
