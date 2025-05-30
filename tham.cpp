#include "carpet.h"
#include <GL/glut.h>

void drawCarpet(float x, float z, float width, float depth) {
    // Vẽ tấm thảm nằm trên mặt phẳng XZ (sàn nhà)
    glColor3f(0.8f, 0.5f, 0.2f); // Màu nâu cam
    glBegin(GL_QUADS);
    glVertex3f(x, 0.0f, z);
    glVertex3f(x + width, 0.0f, z);
    glVertex3f(x + width, 0.0f, z + depth);
    glVertex3f(x, 0.0f, z + depth);
    glEnd();

    // Vẽ viền
    glColor3f(0.3f, 0.2f, 0.1f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, 0.01f, z);
    glVertex3f(x + width, 0.01f, z);
    glVertex3f(x + width, 0.01f, z + depth);
    glVertex3f(x, 0.01f, z + depth);
    glEnd();
}
