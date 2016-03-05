#ifndef LIGHT_H_
#define LIGHT_H_

#include <Eigen/Dense>

struct Light {
    Eigen::Vector3f pos;
    float intensity;

    Light(const Eigen::Vector3f& _pos, float _intensity) :
        pos(_pos),
        intensity(_intensity) {}
};

#endif
