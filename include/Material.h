#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"

struct Material {
    Color ka;
    Color kd;
    Color ks;
    float sp;

    Material (const Color& _ka, const Color& _kd, const Color& _ks, float _sp) :
        ka(_ka),
        kd(_kd),
        ks(_ks),
        sp(_sp) {}

};

#endif
