#include <gtest/gtest.h>
#include <glog/logging.h>

#include "VoxelGrid.hpp"


struct Point {
  double x;
  double y;
  double z;
};


/// {
struct SpecificationCustom: IV::VoxelSpecifications<Point, 2, 2, 1> {
    static constexpr std::size_t Points = 3;
};
TEST(VoxelGrid, SpecicationCustom) {
  using IndexMapper = IV::VoxelGridIndexMapper<SpecificationCustom>;
  using VoxelIndex = typename IndexMapper::VoxelIndex;

  ASSERT_EQ(3, size_t(VoxelIndex::BitsI));
  ASSERT_EQ(3, size_t(VoxelIndex::BitsJ));
  ASSERT_EQ(2, size_t(VoxelIndex::BitsK));
  ASSERT_EQ(0, size_t(VoxelIndex::BitsUndefined));
}
/// }

TEST(VoxelGrid, BitsMaxSize) {
  using Specification =
    IV::VoxelSpecifications<Point,
                            8388608 / 2 - 1,
                            8388608 / 2 - 1,
                             262144 / 2 - 1>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using VoxelIndex = typename IndexMapper::VoxelIndex;

  IndexMapper mapper; (void) mapper;

  ASSERT_EQ(23, size_t(VoxelIndex::BitsI));
  ASSERT_EQ(23, size_t(VoxelIndex::BitsJ));
  ASSERT_EQ(18, size_t(VoxelIndex::BitsK));

  using IJK_Bits = typename VoxelIndex::IJK_Bits;

  do {
    ssize_t i = (1 << 23) / 2 - 1;
    ssize_t j = (1 << 23) / 2 - 1;
    ssize_t k = (1 << 18) / 2 - 1;
    IJK_Bits ijk(i, j, k);

    ASSERT_EQ(i, ijk.i);
    ASSERT_EQ(j, ijk.j);
    ASSERT_EQ(k, ijk.k);

    ijk.i++;
    ijk.j++;
    ijk.k++;

    ASSERT_NE(i + 1, ijk.i);
    ASSERT_NE(j + 1, ijk.j);
    ASSERT_NE(k + 1, ijk.k);
  } while (0);

  do {
    ssize_t i = -(1 << 23) / 2;
    ssize_t j = -(1 << 23) / 2;
    ssize_t k = -(1 << 18) / 2;
    IJK_Bits ijk(i, j, k);

    ASSERT_EQ(i, ijk.i);
    ASSERT_EQ(j, ijk.j);
    ASSERT_EQ(k, ijk.k);

    ijk.i--;
    ijk.j--;
    ijk.k--;

    ASSERT_NE(i - 1, ijk.i);
    ASSERT_NE(j - 1, ijk.j);
    ASSERT_NE(k - 1, ijk.k);
  } while (0);
}

#ifdef UINT128_DEFINED
TEST(VoxelGrid, BitsMaxSize128) {
  using Specification =
    IV::VoxelSpecifications<Point,
                            70368744177664 / 2 - 1,
                            70368744177664 / 2 - 1,
                               68719476736 / 2 - 1>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using VoxelIndex = typename IndexMapper::VoxelIndex;

  IndexMapper mapper; (void) mapper;

  ASSERT_EQ(46, size_t(VoxelIndex::BitsI));
  ASSERT_EQ(46, size_t(VoxelIndex::BitsJ));
  ASSERT_EQ(36, size_t(VoxelIndex::BitsK));

  using IJK_Bits = typename VoxelIndex::IJK_Bits;

  do {
    __int128_t i = (__int128_t(1) << 46) / 2 - 1;
    __int128_t j = (__int128_t(1) << 46) / 2 - 1;
    __int128_t k = (__int128_t(1) << 36) / 2 - 1;
    IJK_Bits ijk(i, j, k);

    ASSERT_EQ(i, ijk.i);
    ASSERT_EQ(j, ijk.j);
    ASSERT_EQ(k, ijk.k);

    ijk.i++;
    ijk.j++;
    ijk.k++;

    ASSERT_NE(i + 1, ijk.i);
    ASSERT_NE(j + 1, ijk.j);
    ASSERT_NE(k + 1, ijk.k);
  } while (0);

  do {
    __int128_t i = -(__int128_t(1) << 46) / 2;
    __int128_t j = -(__int128_t(1) << 46) / 2;
    __int128_t k = -(__int128_t(1) << 36) / 2;
    IJK_Bits ijk(i, j, k);

    ASSERT_EQ(i, ijk.i);
    ASSERT_EQ(j, ijk.j);
    ASSERT_EQ(k, ijk.k);

    ijk.i--;
    ijk.j--;
    ijk.k--;

    ASSERT_NE(i - 1, ijk.i);
    ASSERT_NE(j - 1, ijk.j);
    ASSERT_NE(k - 1, ijk.k);
  } while (0);
}
#endif // UINT128_DEFINED

TEST(VoxelGrid, BitsUndefinedIs0) {
  using Specification = IV::VoxelSpecifications<Point, 2, 2, 1>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using VoxelIndex = typename IndexMapper::VoxelIndex;

  ASSERT_EQ(3, size_t(VoxelIndex::BitsI));
  ASSERT_EQ(3, size_t(VoxelIndex::BitsJ));
  ASSERT_EQ(2, size_t(VoxelIndex::BitsK));
  ASSERT_EQ(0, size_t(VoxelIndex::BitsUndefined));
}

TEST(VoxelGrid, BitsUndefinedIsNot0) {
  using Specification = IV::VoxelSpecifications<Point, 2, 2, 2>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;
  using VoxelIndex = typename IndexMapper::VoxelIndex;

  ASSERT_EQ(3, size_t(VoxelIndex::BitsI));
  ASSERT_EQ(3, size_t(VoxelIndex::BitsJ));
  ASSERT_EQ(3, size_t(VoxelIndex::BitsK));
  ASSERT_EQ(7, size_t(VoxelIndex::BitsUndefined));
}

TEST(VoxelGrid, Mapping) {
  using Specification = IV::VoxelSpecifications<Point, 10, 10, 10>;
  using IndexMapper = IV::VoxelGridIndexMapper<Specification>;

  IndexMapper mapper;

  // The 0 element always maps to 0 id.
  ASSERT_EQ(mapper.MapPoint(
              {0.0,
               0.0,
               0.0}).id, 0);

#if !defined(NDEBUG)
  ASSERT_THROW(mapper.MapPoint({11.0, 0.0, 0.0}),
               std::out_of_range);
#endif
}
