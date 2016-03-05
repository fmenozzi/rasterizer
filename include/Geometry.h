#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>

#include <Triangle.h>
#include <Material.h>

struct Geometry {
    std::vector<Triangle> triangles; 
    Material mat;

    Geometry(Triangle* tris, int count, Material _mat) : mat(_mat) {
        triangles = std::vector<Triangle>();
        for (int i = 0; i < count; i++)
            triangles.push_back(tris[i]);
    }
};

#endif
