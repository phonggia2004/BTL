// DongHo.cpp
#include "DongHo.h"
#include "GL/glut.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawClock(float x, float y, float z, float radius) {
    int numMarks = 12;

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 1, -90, 0); // Quay mặt đồng hồ về phía người nhìn

    // Mặt đồng hồ (hình tròn)
    glColor3f(1.0f, 1.0f, 1.0f); // trắng
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0);
    }
    glEnd();

    // Viền đồng hồ
    glColor3f(0.0f, 0.0f, 0.0f); // đen
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, 0.01f);
    }
    glEnd();

    // Vạch giờ
    for (int i = 0; i < numMarks; ++i) {
        float angle = i * 2.0f * M_PI / numMarks;
        float x1 = cos(angle) * (radius * 0.9f);
        float y1 = sin(angle) * (radius * 0.9f);
        float x2 = cos(angle) * radius;
        float y2 = sin(angle) * radius;

        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex3f(x1, y1, 0.02f);
        glVertex3f(x2, y2, 0.02f);
        glEnd();
    }

    // Kim giờ
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0.03f);
    glVertex3f(0.0f, radius * 0.4f, 0.03f);
    glEnd();

    // Kim phút
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0.04f);
    glVertex3f(radius * 0.6f, 0.0f, 0.04f);
    glEnd();

    glPopMatrix();
}