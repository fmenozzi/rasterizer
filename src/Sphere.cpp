#include <Sphere.h>

#include <Eigen/Dense>

#include <Util.h>

#include <cmath>
#include <cstdio>

void Sphere::generate_geometry(int width, int height) {
    int  gNumVertices  = 0;
    int  gNumTriangles = 0;
    int* gIndexBuffer  = nullptr;

    float theta, phi;
    int t;
    
    gNumVertices    = (height - 2) * width + 2;
    gNumTriangles   = (height - 2) * (width - 1) * 2;
    
    // TODO: Allocate an array for gNumVertices vertices.
    Eigen::Vector3f* vertices = new Eigen::Vector3f[gNumVertices];

    gIndexBuffer = new int[3*gNumTriangles];
    
    t = 0;
    for (int j = 1; j < height-1; ++j) {
        for (int i = 0; i < width; ++i) {
            theta = (float) j / (height-1) * M_PI;
            phi   = (float) i / (width-1)  * M_PI * 2;
            
            float   x   = sinf(theta) * cosf(phi);
            float   y   = cosf(theta);
            float   z   = -sinf(theta) * sinf(phi);
            
            // TODO: Set vertex t in the vertex array to {x, y, z}.
            vertices[t] = Eigen::Vector3f(x, y, z); 
            t++;
        }
    }
    
    // TODO: Set vertex t in the vertex array to {0, 1, 0}.
    vertices[t] = Eigen::Vector3f(0, 1, 0);
    t++;
    
    // TODO: Set vertex t in the vertex array to {0, -1, 0}.
    vertices[t] = Eigen::Vector3f(0, -1, 0); 
    t++;
    
    t = 0;
    for (int j = 0; j < height-3; ++j) {
        for (int i = 0; i < width-1; ++i) {
            gIndexBuffer[t++] = j*width + i;
            gIndexBuffer[t++] = (j+1)*width + (i+1);
            gIndexBuffer[t++] = j*width + (i+1);
            gIndexBuffer[t++] = j*width + i;
            gIndexBuffer[t++] = (j+1)*width + i;
            gIndexBuffer[t++] = (j+1)*width + (i+1);
        }
    }
    for (int i = 0; i < width-1; ++i) {
        gIndexBuffer[t++] = (height-2)*width;
        gIndexBuffer[t++] = i;
        gIndexBuffer[t++] = i + 1;
        gIndexBuffer[t++] = (height-2)*width + 1;
        gIndexBuffer[t++] = (height-3)*width + (i+1);
        gIndexBuffer[t++] = (height-3)*width + i;
    }

    // Create triangles
    for (int i = 0; i < gNumTriangles; i++) {
        Eigen::Vector3f a = vertices[gIndexBuffer[3*i + 0]];
        Eigen::Vector3f b = vertices[gIndexBuffer[3*i + 1]];
        Eigen::Vector3f c = vertices[gIndexBuffer[3*i + 2]];

        triangles.push_back(Triangle(a, b, c));
    }

    delete[] gIndexBuffer;
    delete[] vertices;
}

void Sphere::transform_geometry(const Eigen::Matrix4f& xform) {
    for (auto& tri : triangles) {
        // Transformed Cartesian vertex coordinates
        auto a = vec4to3(xform * Eigen::Vector4f(tri.a[0], tri.a[1], tri.a[2], 1.0f));
        auto b = vec4to3(xform * Eigen::Vector4f(tri.b[0], tri.b[1], tri.b[2], 1.0f));
        auto c = vec4to3(xform * Eigen::Vector4f(tri.c[0], tri.c[1], tri.c[2], 1.0f));

        // Transform vertices
        tri.a = a;
        tri.b = b;
        tri.c = c;

        // Transform normal
        tri.n = ((b-a).cross(c-a)).normalized();

        // Transform vertex normals
        tri.an = (a-center).normalized();
        tri.bn = (b-center).normalized();
        tri.cn = (c-center).normalized();
    }
}
