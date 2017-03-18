#ifndef IV_CORRELATION_CENTROID_HPP_
#define IV_CORRELATION_CENTROID_HPP_

#include <Eigen/Eigen>
#include "detail/RunningRegression.hpp"


namespace IV {
template <typename Specification>
class CorrelationPoint {
public:
  using Point = typename Specification::Point;
  using PointAccessor = typename Specification::PointAccessor;
  using Number = typename Point::Number;
  using Matrix = Eigen::Matrix<Number, 3, 3>;

  void
  operator()(Point point)
  {
    const auto& x = PointAccessor::GetX(point);
    const auto& y = PointAccessor::GetY(point);
    const auto& z = PointAccessor::GetZ(point);

    xy(x, y);
    xz(x, z);
    yz(y, z);
  }

  Matrix
  CorrelationMatrix() const
  {
    auto cxy = xy.Correlation();
    auto cxz = xz.Correlation();
    auto cyz = yz.Correlation();

    Matrix m;
    m <<  1, cxy,  cxz,
        cxy,   1,  cyz,
        cxz, cxy,    1;
    return m;
  }

private:
  detail::RunningRegression<Number> xy;
  detail::RunningRegression<Number> xz;
  detail::RunningRegression<Number> yz;
};
} // ns IV

#endif // IV_CORRELATION_CENTROID_HPP_
