#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>

#include <Eigen/Dense>

#include <Triangle.h>
#include <Material.h>

struct Geometry {
    std::vector<Triangle> triangles; 
    Material mat;
    Eigen::Matrix4f xform;

    Geometry(Material _mat, const Eigen::Matrix4f& _xform) : mat(_mat), xform(_xform) {
        triangles = std::vector<Triangle>();
    }
};

#endif
