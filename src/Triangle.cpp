#include <Triangle.h>


Color Triangle::shade(const Eigen::Vector3f& p, const Eigen::Vector3f& n, const Light& light, const Material& mat) const {

    float Ia = 0.2f;

    // Calculate v, l, and h
    Eigen::Vector3f v = (-p).normalized();
    Eigen::Vector3f l = (light.pos - p).normalized();
    Eigen::Vector3f h = (v+l).normalized();

    /*
    printf("v = (%f, %f, %f)\n", v[0], v[1], v[2]);
    printf("l = (%f, %f, %f)\n", l[0], l[1], l[2]);
    printf("h = (%f, %f, %f)\n", h[0], h[1], h[2]);
    printf("\n");
    */

    // Apply ambient, diffuse, and specular (Phong) shading
    float I = light.intensity;
    Color La = mat.ka * Ia;
    Color Ld = mat.kd * I * std::max(0.0f, n.dot(l));
    Color Ls = mat.ks * I * std::pow(std::max(0.0f, n.dot(h)), mat.sp);

    //printf("Ls = (%f, %f, %f)\n", Ls.r, Ls.g, Ls.b);

    /*
    printf("La = (%f, %f, %f)\n", La.r, La.g, La.b);
    printf("Ld = (%f, %f, %f)\n", Ld.r, Ld.g, Ld.b);
    printf("Ls = (%f, %f, %f)\n", Ls.r, Ls.g, Ls.b);
    printf("\n");
    */

    return La + Ld + Ls;
}
