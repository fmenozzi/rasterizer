#ifndef SPHERE_H_
#define SPHERE_H_

#include <Eigen/Dense>

#include <Geometry.h>

struct Sphere : public Geometry {
    Eigen::Vector3f center;

    Sphere(Material _mat, const Eigen::Matrix4f& _xform) : Geometry(_mat, _xform) {
        generate_geometry(32, 16);
        transform_geometry(xform);

        // TODO: Come up with better way of setting center
        center = Eigen::Vector3f(0,0,-7);
    }

    void generate_geometry(int width, int height);
    void transform_geometry(const Eigen::Matrix4f& xform);
};

#endif
