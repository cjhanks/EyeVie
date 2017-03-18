#ifndef DETAIL_VOXEL_HPP_
#define DETAIL_VOXEL_HPP_

#include <cmath>
#include <cstring>

namespace IV { namespace detail {
/// {
/// @struct IJK_Bits
/// If the dimensions of the I, J, and K do not fit perfectly into an integer
/// boundary (8, 16, 32...) there are some undefined bits which need to be
/// diligantly initialized to 0.
///
/// However, when they *do* perfectly fit onto the boundary usage of
/// `long undefined:0` is ill formed C++ code.  This code works around that
/// issue with a specialization.
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

  long long i:BitsI;
  long long j:BitsJ;
  long long k:BitsK;
  long long undefined:BitsUndefined;

  using BitsTypeI = decltype(i);
  using BitsTypeJ = decltype(j);
  using BitsTypeK = decltype(k);
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

  long long i:BitsI;
  long long j:BitsJ;
  long long k:BitsK;

  using BitsTypeI = decltype(i);
  using BitsTypeJ = decltype(j);
  using BitsTypeK = decltype(k);
};
/// }


/// {
/// At compile time recursively identify the number of bits required to
/// fulfill some number `Size`.  Increment the `Shift` operator until
/// the value of `Size` is 0.
template <std::size_t Size, std::size_t Shift>
struct BitsRequired_ {
  static constexpr std::size_t value =
      1 + BitsRequired_<Size, (Shift >> 1)>::value;
};

template <std::size_t Size>
struct BitsRequired_<Size, 0> {
  static constexpr std::size_t value = 0;
};

template <std::size_t Size>
struct BitsRequired {
  static constexpr std::size_t value =
      1 + BitsRequired_<Size, (Size >> 1)>::value;
};
/// }

/// {
/// Given some number of bits, find the minimum bytes it would require.
template <std::size_t BitSize>
struct BytesRequired {
  static constexpr std::size_t value =
            std::floor(BitSize / 8) + !!(BitSize % 8);
};
/// }

/// {
/// Align the ByteSize to a power of 2 and typedef the required underlying
/// integral type.
///
/// Note:  This is somewhat hacky, it will recursively grow by 1 until the next
/// template specialization.  Meaning, if your required ByteSize is larger than
/// the maximum suported integral type... it will reach the maximum recursion
/// depth at compile time (and give a somewhat confusing error).
template <std::size_t ByteSize>
struct TypeFor_ {
  using type = typename TypeFor_<ByteSize + 1>::type;
};

template <>
struct TypeFor_<1> { using type = std::uint8_t; };
template <>
struct TypeFor_<2> { using type = std::uint16_t; };
template <>
struct TypeFor_<4> { using type = std::uint32_t; };
template <>
struct TypeFor_<8> { using type = std::uint64_t; };
#if UINT128_DEFINED
#if __GNUC__
template <>
struct TypeFor_<16> { using type = __uint128_t; };
#else
# warn Uint128 Not Definde
#endif
#endif
/// }

/// {
/// Compute the required underlying type of the index value.
template <std::size_t BitLength_>
struct TypeFor {
  static constexpr std::size_t BitLength = BitLength_;
  static constexpr std::size_t ByteLength = std::ceil(BitLength / 8.0);

  using type = typename TypeFor_<ByteLength>::type;
};
/// }

template <
  typename Type,
  std::size_t BitsI,
  std::size_t BitsJ,
  std::size_t BitsK
  >
struct BitsUndefined {
  // FIXME: This assume 64bit system.
  static constexpr
  std::size_t value = (8 * sizeof(Type)) - (BitsI + BitsJ + BitsK);
};
} // ns detail
} // ns IV

#endif // DETAIL_VOXEL_HPP_
