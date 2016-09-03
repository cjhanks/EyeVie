#ifndef VOXEL_QUERY_HPP_
#define VOXEL_QUERY_HPP_

#include <vector>
#include "Voxel.hpp"


namespace IV { namespace detail {
template <typename VoxelGrid>
class PointAccessor {
public:
  using PointElement = typename VoxelGrid::PointElement;
  using PointVector = typename VoxelGrid::PointVector;
  using VoxelData = typename VoxelGrid::VoxelData;
  using VoxelIndex = typename VoxelGrid::VoxelIndex;

  PointAccessor()
    : index(0)
    , voxel(nullptr)
  {}

  PointAccessor(VoxelIndex index_, VoxelData* voxel_)
    : index(index_)
    , voxel(voxel_)
  {}

  size_t
  size() const {
    if (voxel == nullptr) {
      return 0;
    } else {
      return voxel->points.size();
    }
  }

  PointElement
  at(std::size_t n)
  {
    const auto& rawPoint = voxel->points.at(n);
    return VoxelGrid::PointLocalToPointGlobal(index, voxel->at(n));
  }

private:
  VoxelIndex index;
  VoxelData* voxel;
};


template <typename VoxelGrid>
class VoxelNeighborhood {
public:
  using VoxelIndex = typename VoxelGrid::VoxelIndex;
  using PointAccessor = typename VoxelGrid::PointAccessor;
  using IndexPointPair = std::pair<VoxelIndex, PointAccessor>;
  using PointPairVector = std::vector<IndexPointPair>;
  using iterator = typename PointPairVector::iterator;


  VoxelNeighborhood(
      VoxelGrid& voxelGrid,
      VoxelIndex center,
      ssize_t size)
    : voxelGrid(voxelGrid)
  {
    for (ssize_t i = -size; i <= size; ++i)
    for (ssize_t j = -size; j <= size; ++j)
    for (ssize_t k = -size; k <= size; ++k) {
      VoxelIndex index(center.i + i,
                       center.j + j,
                       center.k + k);
      accessors.push_back(
          std::make_pair(index, voxelGrid.at(index)));
    }
  }

  iterator
  begin() {
   return accessors.begin();
  }

  iterator
  end() {
   return accessors.end();
  }

private:
  VoxelGrid& voxelGrid;
  PointPairVector accessors;
};

} // ns detail
} // ns IV

#endif // VOXEL_QUERY_HPP_
