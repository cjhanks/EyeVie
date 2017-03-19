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
  
    `
  