# IV - EyeVoxel

A header only C++ voxel library designed for supporting very large grids.

The `IV::VoxelGrid` will change its indexing strategy based on compile-time
constants defining the upper bounds of the coordinate space.  This adaptation
removes floating point calculations from computing the storage index (assuming
no quantization is performed).

The theoretically supported upper bound for the coordinate space volume is
equal equal to: `std::numeric_limits<std::uint128_t>::max() = X * Y * Z`.

There are a few other classes which may be convenient.


## Basics

### `IV::Specification`

The template parameter of nearly all structures and algorithms accepts a
`IV::Specification` structure that defines `constexpr` values and `typename`
definitions.

Sections below describe how different parameters are filled.

### `IV::Specification::{Point,PointAccessor}`

If you need to borrow point types from libraries such as `Eigen` or `PCL` or
you even have your own special snowflake, you can.

A point can be anything you like, let's say it follows the popular convention:

    union MyPoint {
         struct {
            float x;
            float y;
            float z;
        };

        float xyz[4];
    };

You could define either one of these equivalent accessors:

    struct PointAccessor {
        float& GetX(MyPoint& pt) { return pt.x; }
        float& GetY(MyPoint& pt) { return pt.y; }
        float& GetZ(MyPoint& pt) { return pt.z; }
    };

    struct PointAccessor {
        float& GetX(MyPoint& pt) { return pt.xyz[0]; }
        float& GetY(MyPoint& pt) { return pt.xyz[1]; }
        float& GetZ(MyPoint& pt) { return pt.xyz[2]; }
    };


## Structures

### `IV::CentroidPoint`

A structure you probably expect.   It maintains a running mean of of the
`<X, Y, Z>` centroid is for a voxel.


### `IV::CorrelationPoint`

Allows you to extract both the correlation and covariance matrix for a voxel in
`O(1)` time.  This point also has a constant memory overhead.

This structure is particularly useful when paired with `Eigen::EigenSolver<...>`
for computing voxel planarity in constant time (minus the EigenSolver).


### `IV::OccupancyPoint<size_t X, size_t Y, size_t Z>`

A structure for further subsampling a voxel into an occupancy grid.

For example, let's say you have an `IV::VoxelGrid` holding points stored in
meters.  And you have a `Quantizer(0.16)` which is sampling points into 16cm^3
voxels.  You can further divide the space into an occupancy grid with 2cm^3
accuracy by specifying `IV::OccupancyPoint<...>`.

This is an example in 2D: `IV::OccupancyPoint<4, 4, 4>`

     <-{  16 cm  }->
    |               |
    +---+---+---+---+
    | 0 | 1 | 0 | 0 |
    +---+---+---+---+
    | 0 | 1 | 0 | 0 |
    +---+---+---+---+
    | 0 | 1 | 1 | 0 |
    +---+---+---+---+
    | 0 | 0 | 1 | 1 |
    +---+---+---+---+
    ^   ^
    |   |
    {4cm}


This is an example in 2D: `IV::OccupancyPoint<2, 2, 2>`

     <-{16cm}->
     |       |
     +---+---+
     | 0 | 1 |
     +---+---+
     | 0 | 1 |
     +---+---+
     ^   ^
     |   |
     {8cm}
