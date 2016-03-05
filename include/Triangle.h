#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <Eigen/Dense>

#include <BoundingBox.h>
#include <Color.h>

struct Triangle {
    // Vertices
    Eigen::Vector3f a;
    Eigen::Vector3f b;
    Eigen::Vector3f c;

    // Triangle normal
    Eigen::Vector3f n;

    Triangle(const Eigen::Vector3f& _a, const Eigen::Vector3f& _b, const Eigen::Vector3f& _c) :
        a(_a),
        b(_b),
        c(_c),
        n(((b-a).cross(c-a)).normalized()) {}

    BoundingBox bounds() {
        return BoundingBox(a, b, c);
    }

    Eigen::Vector3f centroid() {
        return 1/3.0f*a + 1/3.0f*b + 1/3.0f*c;
    }
};

#endif
