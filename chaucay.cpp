#include "chaucay.h"
#include <GL/glut.h>

void drawPlantPot() {
    GLUquadric* quad = gluNewQuadric();

    // Chậu (hình trụ úp)
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f); // Đưa lên khỏi mặt sàn
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Xoay dọc theo trục Y
    glColor3f(0.6f, 0.3f, 0.1f); // Màu nâu
    gluCylinder(quad, 0.3f, 0.2f, 0.4f, 32, 32); // Đáy to hơn miệng
    glPopMatrix();

    // Thân cây (hình trụ đứng)
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f); // cao hơn chậu
    glColor3f(0.4f, 0.2f, 0.1f); // Màu thân gỗ
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.05f, 0.05f, 0.5f, 16, 16);
    glPopMatrix();

    // Tán cây (hình cầu xanh)
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f); // Trên thân cây
    glColor3f(0.0f, 0.6f, 0.0f); // Màu xanh lá
    glutSolidSphere(0.35, 32, 32);
    glPopMatrix();

    gluDeleteQuadric(quad);
}
