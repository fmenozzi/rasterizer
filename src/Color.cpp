#include "Color.h"

#include <cmath>

Color Color::correct(float gamma) const {
    float exp = 1/gamma;
    return Color(std::pow(r,exp), std::pow(g,exp), std::pow(b,exp));
}
