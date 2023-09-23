#ifndef VOXEL_HPP_
#define VOXEL_HPP_

#include <cstring>
#include <cstdint>

#include "ByteManipulation.hpp"


namespace IV { namespace detail {
template <
  std::size_t BitsI,
  std::size_t BitsJ,
  std::size_t BitsK,
  std::size_t BitsUndefined
  >
struct IJK_Bits {
  IJK_Bits(long i, long j, long k)
    : i(i)
    , j(j)
    , k(k)
    , undefined(0)
  {}

  long i:BitsI;
  long j:BitsJ;
  long k:BitsK;
  long undefined:BitsUndefined;
};

template <
  std::size_t BitsI,
  std::size_t BitsJ,
  std::size_t BitsK
  >
struct IJK_Bits<BitsI, BitsJ, BitsK, 0> {
  IJK_Bits(long i, long j, long k)
    : i(i)
    , j(j)
    , k(k)
  {}

  long i:BitsI;
  long j:BitsJ;
  long k:BitsK;
};

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

  static constexpr
  std::size_t BitsUndefined = (8 * sizeof(IndexType))
                            - (BitsI + BitsJ + BitsK);

  using IJK_Bits = IV::detail::IJK_Bits<BitsI, BitsJ, BitsK, BitsUndefined>;

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
    : ijk(i, j, k)
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
    IJK_Bits ijk;
    //struct {
    //  long i:BitsI;
    //  long j:BitsJ;
    //  long k:BitsK;
    //  long undefined:BitsUndefined;
    //} __attribute__((packed));

   IndexType id;
  };
  // }
};
/// }
} // ns detail
} // ns IV

#endif // VOXEL_HPP_
