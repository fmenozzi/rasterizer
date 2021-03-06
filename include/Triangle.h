#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <Eigen/Dense>

#include <BoundingBox.h>
#include <Color.h>
#include <Material.h>
#include <Light.h>

struct Triangle {
    // Vertices
    Eigen::Vector3f a;
    Eigen::Vector3f b;
    Eigen::Vector3f c;

    // Triangle normal
    Eigen::Vector3f n;

    // Vertex normals
    Eigen::Vector3f an;
    Eigen::Vector3f bn;
    Eigen::Vector3f cn;

    Triangle(const Eigen::Vector3f& _a, const Eigen::Vector3f& _b, const Eigen::Vector3f& _c) :
        a(_a),
        b(_b),
        c(_c) {}

    BoundingBox bounds() const {
        return BoundingBox(a, b, c);
    }

    Eigen::Vector3f centroid() const {
        return 1/3.0f*a + 1/3.0f*b + 1/3.0f*c;
    }

    Color shade(const Eigen::Vector3f& p, const Eigen::Vector3f& n, const Light& light, const Material& mat) const;
};

#endif
