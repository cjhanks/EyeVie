#ifndef IV_POINT_HPP_
#define IV_POINT_HPP_

namespace IV {
template <typename Specification>
struct DefaultPointData {
};

struct DefaultPoint {
  using Number = float;

  union {
    struct {
      Number x;
      Number y;
      Number z;
    };

    Number xyz[3];
  };
};

template <typename Point>
struct PointAccessor {
  using Number = typename Point::Number;

  static Number&
  GetX(Point& point)
  { return point.x; }

  static Number&
  GetY(Point& point)
  { return point.y; }

  static Number&
  GetZ(Point& point)
  { return point.z; }
};
} // ns IV

#endif // IV_POINT_HPP_
