#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_

#include <Eigen/Dense>

struct BoundingBox {
    int xmin;
    int xmax;
    int ymin;
    int ymax;

    BoundingBox(const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c) {
        xmin = std::min(a[0], std::min(b[0], c[0]));
        xmax = std::max(a[0], std::max(b[0], c[0]));
        ymin = std::min(a[1], std::min(b[1], c[1]));
        ymax = std::max(a[1], std::max(b[1], c[1]));
    }
};

#endif
