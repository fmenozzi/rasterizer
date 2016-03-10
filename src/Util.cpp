#include <Util.h>

Eigen::Vector3f vec4to3(const Eigen::Vector4f& v) {
    return Eigen::Vector3f(v[0]/v[3], v[1]/v[3], v[2]/v[3]);
}
