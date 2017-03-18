#include <gtest/gtest.h>

#include "Voxel.hpp"


TEST(Voxel, Bits) {
  using namespace IV::detail;

  ASSERT_EQ(size_t(BitsRequired<1 << 0>::value), 0 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 1>::value), 1 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 2>::value), 2 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 3>::value), 3 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 4>::value), 4 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 5>::value), 5 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 6>::value), 6 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 7>::value), 7 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 8>::value), 8 + 1);
  ASSERT_EQ(size_t(BitsRequired<1 << 9>::value), 9 + 1);
}

TEST(Voxel, Bytes) {
  using namespace IV::detail;

  ASSERT_EQ(size_t(BytesRequired<0>::value), 0);
  ASSERT_EQ(size_t(BytesRequired<1>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<2>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<3>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<4>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<5>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<6>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<7>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<8>::value), 1);
  ASSERT_EQ(size_t(BytesRequired<9>::value), 2);
  ASSERT_EQ(size_t(BytesRequired<16>::value), 2);
  ASSERT_EQ(size_t(BytesRequired<17>::value), 3);
  ASSERT_EQ(size_t(BytesRequired<32>::value), 4);
  ASSERT_EQ(size_t(BytesRequired<33>::value), 5);
  ASSERT_EQ(size_t(BytesRequired<64>::value), 8);
  ASSERT_EQ(size_t(BytesRequired<65>::value), 9);
}

TEST(Voxel, Types) {
  using namespace IV::detail;

  ASSERT_TRUE((std::is_same<TypeFor<0>::type, std::uint8_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<8>::type, std::uint8_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<9 >::type, std::uint16_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<16>::type, std::uint16_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<17>::type, std::uint32_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<32>::type, std::uint32_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<33>::type, std::uint64_t>::value));
  ASSERT_TRUE((std::is_same<TypeFor<64>::type, std::uint64_t>::value));
}

TEST(Voxel, Hashing) {
  using namespace IV;
  using VoxelIndex = IV::VoxelIndex<10, 10, 10>;

  VoxelIndex index(0, 0, 0);
  ASSERT_EQ(0, index.id);
}
