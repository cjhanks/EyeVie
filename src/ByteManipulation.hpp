///////////////////////////////////////////////////////////////////////////////
// Tools for computing types/sizes at compile time.
///////////////////////////////////////////////////////////////////////////////
#ifndef BYTE_MANIPULATION_HPP_
#define BYTE_MANIPULATION_HPP_

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>


namespace IV { namespace detail {
/// {
/// At compile time recursively identify the number of bits required to
/// fulfill /// some number `Size`.  Increment the `Shift` operator until
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
#if 0
template <>
struct TypeFor_<16> { using type = std::uint128_t; };
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
} // ns detail
} // ns IV

#endif // BYTE_MANIPULATION_HPP_
