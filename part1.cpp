#include <cstdio>

#if defined(USE_OPENGL)
    #include <GL/glut.h>
#endif

#include <Eigen/Dense>

#include <Color.h>

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

int main(int argc, char* argv[]) {
    // White buffer
    buffer = new Color[NX*NY];
    for (int i = 0; i < NX; i++)
        for (int j = 0; j < NY; j++)
            buffer[i*NY + j] = Color(1.0f, 1.0f, 1.0f);

    // Test that Eigen is working properly
    Eigen::Matrix4f m;
    int k = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m(i,j) = k++;
    std::cout << m << std::endl;

    #if defined(USE_OPENGL)
        // Write buffer to OpenGL window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(NX, NY);
        glutCreateWindow("Part 1");
        glutDisplayFunc(gl_display);
        glutKeyboardFunc(gl_keyboard);
        glutMainLoop();
    #else
        // Write buffer to image file
        FILE* fp = fopen("images/part1.ppm", "w");
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
