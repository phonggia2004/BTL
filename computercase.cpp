#include <GL/glut.h>
#include "ComputerCase.h"

void drawComputerCase(float x, float y, float z, float rotationY) {
    GLfloat caseColor[] = { 0.1f, 0.1f, 0.15f }; // Gần đen
    GLfloat frontPanelColor[] = { 0.15f, 0.15f, 0.2f };
    GLfloat buttonColor[] = { 0.8f, 0.1f, 0.1f }; // Đỏ cho nút nguồn
    GLfloat usbColor[] = { 0.3f, 0.7f, 1.0f };

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // CASE chính
    glColor3fv(caseColor);
    glPushMatrix();
    glScalef(0.35f, 0.7f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Mặt trước (gắn chi tiết vào)
    glColor3fv(frontPanelColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.25f); // đẩy ra phía trước của case
    glScalef(0.34f, 0.68f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Nút nguồn
    glColor3fv(buttonColor);
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.26f);
    glutSolidSphere(0.015, 10, 10);
    glPopMatrix();

    // USB 1
    glColor3fv(usbColor);
    glPushMatrix();
    glTranslatef(0.08f, 0.05f, 0.26f);
    glScalef(0.04f, 0.015f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // USB 2
    glPushMatrix();
    glTranslatef(-0.08f, 0.05f, 0.26f);
    glScalef(0.04f, 0.015f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}
