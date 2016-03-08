#include <Sphere.h>

#include <Eigen/Dense>

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
    for (size_t i = 0; i < triangles.size(); i++) {
        Eigen::Vector4f a4(triangles[i].a[0], triangles[i].a[1], triangles[i].a[2], 1.0f);
        Eigen::Vector4f b4(triangles[i].b[0], triangles[i].b[1], triangles[i].b[2], 1.0f);
        Eigen::Vector4f c4(triangles[i].c[0], triangles[i].c[1], triangles[i].c[2], 1.0f);

        a4 = xform * a4;
        b4 = xform * b4;
        c4 = xform * c4;

        triangles[i].a = a4.head<3>();
        triangles[i].b = b4.head<3>();
        triangles[i].c = c4.head<3>();
    }
}
