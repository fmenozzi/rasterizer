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

}

void rasterize(const Sphere& sphere) {
    for (const auto& triangle : sphere.triangles)
        rasterize(triangle);
}

int main(int argc, char* argv[]) {
    constexpr float l = -0.1f;
    constexpr float r =  0.1f;
    constexpr float b = -0.1f;
    constexpr float t =  0.1f;
    constexpr float n = -0.1f;
    constexpr float f =  0.1f;

    Eigen::Matrix4f M, M_mod, M_cam, M_persp, M_vp;

    // Modeling transform (i.e. scale by two and translate to (0,0,-7))
    M_mod <<   2.0f,            0.0f,           0.0f,           0.0f,
               0.0f,            2.0f,           0.0f,           0.0f,
               0.0f,            0.0f,           2.0f,          -7.0f,
               0.0f,            0.0f,           0.0f,           1.0f;

    // Camera transform
    M_cam <<   1.0f,            0.0f,           0.0f,           0.0f,
               0.0f,            1.0f,           0.0f,           0.0f,
               0.0f,            0.0f,           1.0f,           0.0f,
               0.0f,            0.0f,           0.0f,           1.0f;

    // Perspective transform
    M_persp << 2.0f*n/(r-l),    0.0f,           (l+r)/(l-r),    0.0f,
               0.0f,            2.0f*n/(t-b),   (b+t)/(b-t),    0.0f,
               0.0f,            0.0f,           (f+n)/(n-f),    2.0f*f*n/(f-n),
               0.0f,            0.0f,           1.0f,           0.0f;

    // Viewport transform
    M_vp <<    NX/2.0f,         0.0f,           0.0f,           (NX-1)/2.0f,
               0.0f,            NY/2.0f,        0.0f,           (NY-1)/2.0f,
               0.0f,            0.0f,           1.0f,           0.0f,
               0.0f,            0.0f,           0.0f,           1.0f;

    // Final transform
    //M = M_vp * M_persp * M_cam * M_mod;
    M = M_mod;

    // Sphere
    Color ka(0.0f, 1.0f, 0.0f);
    Color kd(0.0f, 0.5f, 0.0f);
    Color ks(0.5f, 0.5f, 0.5f);
    Sphere sphere(Material(ka, kd, ks, 32), M);

    /*
    for (const auto& tri : sphere.triangles) {
        Eigen::Vector3f center_to_a = tri.a - sphere.center;
        Eigen::Vector3f center_to_b = tri.b - sphere.center;
        Eigen::Vector3f center_to_c = tri.c - sphere.center;

        printf("(%f, %f, %f), mag=%f\n", center_to_a[0], center_to_a[1], center_to_a[2], center_to_a.norm());
        printf("(%f, %f, %f), mag=%f\n", center_to_b[0], center_to_b[1], center_to_b[2], center_to_b.norm());
        printf("(%f, %f, %f), mag=%f\n", center_to_c[0], center_to_c[1], center_to_c[2], center_to_c.norm());
        printf("\n");
    } 
    */

    // Black buffer
    buffer = new Color[NX*NY];
    for (int x = 0; x < NX; x++)
        for (int y = 0; y < NY; y++)
            draw(x, y, Color(0,0,0));

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
