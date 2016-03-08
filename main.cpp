#include <cstdio>

#if defined(USE_OPENGL)
    #include <GL/glut.h>
#endif

#include <Eigen/Dense>

#include <Color.h>
#include <Material.h>
#include <Light.h>
#include <Sphere.h>

#include <iostream>

constexpr int NX = 512;
constexpr int NY = 512;

Color* buffer;

void cleanup() {
    delete[] buffer;
}

#if defined(USE_OPENGL)
    void gl_display() {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        float* float_buffer = new float[3*NX*NY];

        int k = 0;
        for (int i = 0; i < NX; i++) {
            for (int j = 0; j < NY; j++) {
                float_buffer[k++] = buffer[j*NY + i].r;
                float_buffer[k++] = buffer[j*NY + i].g;
                float_buffer[k++] = buffer[j*NY + i].b;
            }
        }

        glDrawPixels(NX, NY, GL_RGB, GL_FLOAT, float_buffer);

        glutSwapBuffers();

        delete[] float_buffer;
    }

    void gl_keyboard(unsigned char key, int x, int y) {
        switch (key) {
            // ESC
            case 27:
                cleanup();
                exit(EXIT_SUCCESS);
        }
    }
#endif

void draw(int x, int y, const Color& color) {
    buffer[x*NY + y] = color;
}

void rasterize(const Triangle& tri) {
    printf("Rasterize called\n");

    // Get bounding box
    BoundingBox bb = tri.bounds();

    // Vertices
    float ax = tri.a[0];
    float ay = tri.a[1];
    float bx = tri.b[0];
    float by = tri.b[1];
    float cx = tri.c[0];
    float cy = tri.c[1];

    // Bounding box width
    float width = bb.xmax - bb.xmin;

    // Beta setup
    float beta_denom = (ay-cy)*bx + (cx-ax)*by + ax*cy - cx*ay;
    float beta_x = (ay-cy) / beta_denom;
    float beta_y = (cx-ax) / beta_denom;

    // Gamma setup
    float gamma_denom = (ay-by)*cx + (bx-ax)*cy + ax*by - bx*ay;
    float gamma_x = (ay-by) / gamma_denom;
    float gamma_y = (bx-ax) / gamma_denom;

    float beta, gamma;
    for (int y = bb.ymin; y <= bb.ymax; y++) {
        for (int x = bb.xmin; x <= bb.xmax; x++) {
            beta  = ((ay-cy)*x + (cx-ax)*y + ax*cy - cx*ay) / beta_denom;
            gamma = ((ay-by)*x + (bx-ax)*y + ax*by - bx*ay) / gamma_denom;

            if (beta >= 0 && gamma >= 0 && beta + gamma <= 1) {
                    draw(x, y, Color(1,1,1));
            }

            beta  += beta_x;
            gamma += gamma_x;
        }

        beta  += beta_y - width*beta_x;
        gamma += gamma_y - width*gamma_x;
    }
}

int main(int argc, char* argv[]) {
    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;
    constexpr float n = -0.1f;
    constexpr float f = -1000.0f;

    Eigen::Matrix4f M, M_m, M_cam, P, M_orth, M_vp;

    // Modeling transform (i.e. scale by 2 and translate to (0,0,-7))
    M_m <<     2.0f,            0.0f,           0.0f,           0.0f,
               0.0f,            2.0f,           0.0f,           0.0f,
               0.0f,            0.0f,           2.0f,          -7.0f,
               0.0f,            0.0f,           0.0f,           1.0f;

    // Camera transform
    M_cam <<   1.0f,            0.0f,           0.0f,           0.0f,
               0.0f,            1.0f,           0.0f,           0.0f,
               0.0f,            0.0f,           1.0f,           0.0f,
               0.0f,            0.0f,           0.0f,           1.0f;

    // Perspective transform
    P <<       n,               0.0f,           0.0f,           0.0f,
               0.0f,            n,              0.0f,           0.0f,
               0.0f,            0.0f,           n+f,            -f*n,
               0.0f,            0.0f,           1.0f,           0.0f;

    // Orthographic transform
    M_orth <<  2.0f/(r-l),      0.0f,           0.0f,           -(r+l)/(r-l),
               0.0f,            2.0f/(t-b),     0.0f,           -(t+b)/(t-b),
               0.0f,            0.0f,           2.0f/(n-f),     -(n+f)/(n-f),
               0.0f,            0.0f,           0.0f,           1.0f;

    // Viewport transform
    M_vp <<    NX/2.0f,         0.0f,           0.0f,           (NX-1)/2.0f,
               0.0f,            NY/2.0f,        0.0f,           (NY-1)/2.0f,
               0.0f,            0.0f,           1.0f,           0.0f,
               0.0f,            0.0f,           0.0f,           1.0f;

    // Final transform
    M = M_vp * M_orth * P * M_cam * M_m;

    std::cout << M << std::endl << std::endl;

    // Sphere
    Color ka(0.0f, 1.0f, 0.0f);
    Color kd(0.0f, 0.5f, 0.0f);
    Color ks(0.5f, 0.5f, 0.5f);
    Sphere sphere(Material(ka, kd, ks, 32), M);

    // Black buffer
    buffer = new Color[NX*NY];
    for (int x = 0; x < NX; x++)
        for (int y = 0; y < NY; y++)
            draw(x, y, Color(0,0,0));

    /*
    Eigen::Vector3f va(100,100,100), vb(100, 200, 100), vc(150, 150, 150);
    Triangle tri(va, vb, vc);
    rasterize(tri);
    */

    /*
    for (size_t i = 0; i < sphere.triangles.size(); i++) {
        Eigen::Vector3f a = sphere.triangles[i].a;
        Eigen::Vector3f b = sphere.triangles[i].b;
        Eigen::Vector3f c = sphere.triangles[i].c;

        printf("(%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n", a[0], a[1], a[2], b[0], b[1], b[2], c[0], c[1], c[2]);
    }
    */

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        #if defined(UNSHADED)
            const char* window_name = "Part 1 (Unshaded)";
        #elif defined(FLAT_SHADING)
            const char* window_name = "Part 2 (Flat Shading)";
        #elif defined(GOURAUD_SHADING)
            const char* window_name = "Part 3 (Gouraud Shading)";
        #elif defined(PHONG_SHADING)
            const char* window_name = "Part 4 (Phong Shading)";
        #endif
        glutCreateWindow(window_name);
        glutDisplayFunc(gl_display);
        glutKeyboardFunc(gl_keyboard);
        glutMainLoop();
    #else
        // Write buffer to image file
        #if defined(UNSHADED)
            const char* ppmpath = "images/part1-unshaded.ppm";
        #elif defined(FLAT_SHADING)
            const char* ppmpath = "images/part2-flat.ppm";
        #elif defined(GOURAUD_SHADING)
            const char* ppmpath = "images/part3-gouraud.ppm";
        #elif defined(PHONG_SHADING)
            const char* ppmpath = "images/part4-phong.ppm";
        #endif
        FILE* fp = fopen(ppmpath, "w");
        fprintf(fp, "P3\n");
        fprintf(fp, "%d %d %d\n", NX, NY, 255);
        for (int i = NX-1; i >= 0; i--) {
            for (int j = 0; j < NY; j++) {
                // Convert float RGB to int RGB
                int ir = (int)(buffer[j*NY + i].r * 255);
                int ig = (int)(buffer[j*NY + i].g * 255);
                int ib = (int)(buffer[j*NY + i].b * 255);

                fprintf(fp, "%d %d %d\n", ir, ig, ib);
            }
        }
        fclose(fp);
    #endif

    cleanup();

    return EXIT_SUCCESS;
}
