#include <Triangle.h>


Color Triangle::shade(const Eigen::Vector3f& p, const Eigen::Vector3f& n, const Light& light, const Material& mat) const {
    // Ambient light intensity
    float Ia = 0.2f;

    // Calculate v, l, and h
    Eigen::Vector3f v = (-p).normalized();
    Eigen::Vector3f l = (light.pos - p).normalized();
    Eigen::Vector3f h = (v+l).normalized();

    // Apply ambient, diffuse, and specular (Phong) shading
    float I = light.intensity;
    Color La = mat.ka * Ia;
    Color Ld = mat.kd * I * std::max(0.0f, n.dot(l));
    Color Ls = mat.ks * I * std::pow(std::max(0.0f, n.dot(h)), mat.sp);

    return La + Ld + Ls;
}
