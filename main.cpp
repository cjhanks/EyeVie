#include "VoxelGrid.hpp"
#include "SuperGrid.hpp"
#include "VoxelContainer.hpp"


#include <sys/resource.h>
#include <sys/time.h>

#include <iostream>


struct Point {
  double x;
  double y;
  double z;

  struct {
  } data;
};

static constexpr size_t MaxXcm = 256 * 100;
static constexpr size_t MaxYcm = 256 * 100;
static constexpr size_t MaxZcm =  50 * 100;
/*
static constexpr size_t MaxXcm = 35 * 1;
static constexpr size_t MaxYcm = 35 * 1;
static constexpr size_t MaxZcm =  5 * 1;
*/

using Specification =
      IV::VoxelSpecifications<
        Point,
        MaxXcm,
        MaxYcm,
        MaxZcm
      >;
using VoxelGrid = IV::VoxelGrid<Specification>;
using SuperGrid = IV::SuperGrid<VoxelGrid>;

std::vector<Point>
GeneratePoints(std::size_t number)
{
  std::vector<Point> points;
  while (number--) {
    Point pt;
    pt.x = (rand() % MaxXcm) / (1 + rand() % MaxXcm);
    pt.y = (rand() % MaxYcm) / (1 + rand() % MaxYcm);
    pt.z = (rand() % MaxZcm) / (1 + rand() % MaxZcm);
    points.push_back(pt);
  }

  return points;
}

void
TestRandomData1(std::size_t number)
{
  Specification specification;
  VoxelGrid grid(specification);

  while (number--) {
    Point pt;
    pt.x = (rand() % MaxXcm) / (1 + rand() % MaxXcm);
    pt.y = (rand() % MaxYcm) / (1 + rand() % MaxYcm);
    pt.z = (rand() % MaxZcm) / (1 + rand() % MaxZcm);
    grid.AddPoint(pt);

    if (number % 100000 == 0)
      std::cerr << number << "\n";
  }
}

void
TestFullyDenseEvenlySampled1()
{
  Specification specification;
  VoxelGrid grid(specification);

  IV::VoxelContainer<VoxelGrid, int> container(specification);

  size_t n = 0;
  for (double i = -double(MaxXcm); i <= double(MaxXcm) ; i += .05)
  for (double j = -double(MaxYcm); j <= double(MaxYcm) ; j += .05)
  for (double k = -double(MaxZcm); k <= double(MaxZcm) ; k += .05) {
    Point pt;
    pt.x = i;
    pt.y = j;
    pt.z = k;

    grid.AddPoint(pt);
    ++n;
  }

  std::cerr << n << "\n";
  SuperGrid::Settings ssettings;
  ssettings.superSampleX = 10;
  ssettings.superSampleY = 10;
  ssettings.superSampleZ = 10;
  SuperGrid super(ssettings, grid);

  Point center;
  center.x = 5;
  center.y = 5;
  center.z = 5;
  auto neighborhood = super.at(center, 1);
  for (const auto& block: neighborhood) {
    std::cerr
      << "["
        << block.first.i << ", "
        << block.first.j << ", "
        << block.first.k << "::"
        << block.second.size()
      << "]\n";
  }
}

int
main()
{
  using namespace std;

  //auto testData = GeneratePoints(500000000);
  //TestFullyDenseEvenlySampled1();
  TestRandomData1(1000000000);

#if 0
                        >;
  Specification specification;
  IV::VoxelGrid<Specification> grid(specification);

  do {
    auto index = grid.MinVoxel();
    cerr << index.i << ", "
         << index.j << ", "
         << index.k << "\n";
  } while (0);

  std::cerr << "-------------------------\n";
  do {
    auto index = grid.MaxVoxel();
    cerr << index.i << ", "
         << index.j << ", "
         << index.k << "\n";
  } while (0);

  std::cerr << "-------------------------\n";
  for (double i = -255.1; i < +256; i += .5)
  for (double j = -255.1; j < +256; j += .5)
  for (double k = -50 ; k < +50 ; k += 2) {
    Point pt;
    pt.x = i;
    pt.y = j;
    pt.z = k;

    //std::cerr << pt.x << ", "
    //          << pt.y << ", "
    //          << pt.z << "\n";
    grid.AddPoint(pt);
  }
#endif

}
