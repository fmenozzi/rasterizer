#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>

#include <Eigen/Dense>

#include <Triangle.h>
#include <Material.h>

struct Geometry {
    std::vector<Triangle> triangles; 
    Material mat;
    Eigen::Matrix4f transform;

    Geometry(Material _mat) : mat(_mat) {
        triangles = std::vector<Triangle>();
    }
};

#endif
