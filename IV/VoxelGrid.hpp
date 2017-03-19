#ifndef IV_VOXEL_GRID_HPP_
#define IV_VOXEL_GRID_HPP_

#include <unordered_map>

#include "Quantization.hpp"
#include "Specification.hpp"
#include "Voxel.hpp"
#include "detail/Static.hpp"


namespace IV {
template <typename Specification_,
          typename PointData_>
class VoxelGrid {
public:
  using Specification = Specification_;
  using Point = typename Specification::Point;
  using PointData = PointData_;
  using VoxelIndex = IV::VoxelIndex<
                          Specification::MaxUnitsX,
                          Specification::MaxUnitsY,
                          Specification::MaxUnitsZ
                      >;

private:
  using Quantizer = IV::Quantizer<Specification>;
  using Map = std::unordered_map<
                    VoxelIndex,
                    PointData,
                    typename VoxelIndex::Hasher
                    >;

public:
  using iterator = typename Map::iterator;
  using const_iterator = typename Map::const_iterator;

  explicit VoxelGrid(Quantizer quantizer)
    : quantizer(quantizer)
  {}

  // {
  // - update access
  void
  operator()(Point point)
  {
    auto index = quantizer.MapPoint(point);
    PointData& voxel = data[index];

    // {
    // - Add to all of the potential method overloads.  Keep in mind
    //   that these function calls compile to no-ops if the method does
    //   not exist on the point.
    detail::PerformOp<
              PointData,
              void()>::Op(voxel);
    detail::PerformOp<
              PointData,
              void(Point)>::Op(voxel, point);
    detail::PerformOp<
              PointData,
              void(Point, Quantizer)>::Op(voxel, point, quantizer);
    // }
  }
  // }

  // {
  // - iterator access
  iterator
  find(Point point)
  { return data.find(quantizer.MapPoint(point)); }

  const_iterator
  find(Point point) const
  { return data.find(quantizer.MapPoint(point)); }

  iterator
  begin()
  { return data.begin(); }

  iterator
  end()
  { return data.end(); }

  const_iterator
  begin() const
  { return data.begin(); }

  const_iterator
  end() const
  { return data.end(); }
  // }

private:
  Quantizer quantizer;
  Map data;
};

} // ns IV

#endif // IV_VOXEL_GRID_HPP_
