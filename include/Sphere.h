#ifndef SPHERE_H_
#define SPHERE_H_

#include <Eigen/Dense>

#include <Geometry.h>

struct Sphere : public Geometry {
    Eigen::Vector3f center;

    Sphere(Material _mat) : Geometry(_mat) {
        generate_geometry(32, 16);
    }

    void generate_geometry(int width, int height);
};

#endif
