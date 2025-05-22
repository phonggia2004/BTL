#include <GL/glut.h>
#include "ComputerMonitor.h"

void drawComputerMonitor() {
    // Màu màn hình và chân đế
    GLfloat monitorColor[] = { 0.1f, 0.1f, 0.1f }; // Đen xám
    GLfloat screenColor[] = { 0.2f, 0.7f, 0.9f };  // Xanh dương nhạt

    // Vẽ khung màn hình
    glColor3fv(monitorColor);
    glPushMatrix();
    glScalef(1.2f, 0.75f, 0.05f);  // Kích thước màn hình (rộng, cao, dày)
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ mặt trước màn hình
    glColor3fv(screenColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.03f); // Đẩy ra trước một chút so với khung
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.6f, -0.375f, 0.0f);
    glVertex3f(0.6f, -0.375f, 0.0f);
    glVertex3f(0.6f, 0.375f, 0.0f);
    glVertex3f(-0.6f, 0.375f, 0.0f);
    glEnd();
    glPopMatrix();

    // Vẽ chân đế
    glColor3fv(monitorColor);
    glPushMatrix();
    glTranslatef(0.0f, -0.45f, 0.0f);
    glScalef(0.3f, 0.1f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ đế
    glPushMatrix();
    glTranslatef(0.0f, -0.55f, 0.1f);
    glScalef(0.7f, 0.05f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
