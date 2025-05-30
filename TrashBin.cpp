#include "TrashBin.h"
#include <cmath>

TrashBin::TrashBin() {
    posX = posY = posZ = 0.0f;
    scaleX = scaleY = scaleZ = 1.0f;
    angleX = angleY = angleZ = 0.0f;
    bodyColorR = 0.5f; bodyColorG = 0.5f; bodyColorB = 0.5f; // Màu xám cho thân thùng
    lidColorR = 0.0f; lidColorG = 0.0f; lidColorB = 0.0f; // Màu đen cho nắp thùng
}

void TrashBin::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void TrashBin::setScale(float sx, float sy, float sz) {
    scaleX = sx;
    scaleY = sy;
    scaleZ = sz;
}

void TrashBin::setRotation(float ax, float ay, float az) {
    angleX = ax;
    angleY = ay;
    angleZ = az;
}

void TrashBin::setBodyColor(float r, float g, float b) {
    bodyColorR = r;
    bodyColorG = g;
    bodyColorB = b;
}

void TrashBin::setLidColor(float r, float g, float b) {
    lidColorR = r;
    lidColorG = g;
    lidColorB = b;
}

void TrashBin::draw() {
    glPushMatrix();
    // Áp dụng các phép biến đổi
    glTranslatef(posX, posY, posZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);

    // Vẽ thân thùng rác (hình trụ)
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f); // Đặt thân thùng ở độ cao y = 0.25
    glScalef(0.2f, 0.5f, 0.2f); // Kích thước: 0.2m (bán kính) x 0.5m (cao) x 0.2m (bán kính)
    int sides = 20;
    glColor3f(bodyColorR, bodyColorG, bodyColorB);
    for (int i = 0; i < sides; i++) {
        float theta1 = (2.0f * 3.14159f * i) / sides;
        float theta2 = (2.0f * 3.14159f * (i + 1)) / sides;
        glBegin(GL_QUADS);
        // Mặt bên
        glNormal3f(cos(theta1), 0.0f, sin(theta1));
        glVertex3f(cos(theta1) * 0.5f, -0.5f, sin(theta1) * 0.5f);
        glVertex3f(cos(theta2) * 0.5f, -0.5f, sin(theta2) * 0.5f);
        glVertex3f(cos(theta2) * 0.5f, 0.5f, sin(theta2) * 0.5f);
        glVertex3f(cos(theta1) * 0.5f, 0.5f, sin(theta1) * 0.5f);
        glEnd();
    }
    // Mặt đáy
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    for (int i = 0; i < sides; i++) {
        float theta = (2.0f * 3.14159f * i) / sides;
        glVertex3f(cos(theta) * 0.5f, -0.5f, sin(theta) * 0.5f);
    }
    glEnd();
    glPopMatrix();

    // Vẽ nắp thùng rác (hình tròn)
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Đặt nắp trên đỉnh thân thùng
    glScalef(0.2f, 0.01f, 0.2f); // Kích thước: 0.2m (bán kính) x 0.01m (dày) x 0.2m (bán kính)
    glColor3f(lidColorR, lidColorG, lidColorB);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < sides; i++) {
        float theta = (2.0f * 3.14159f * i) / sides;
        glVertex3f(cos(theta) * 0.5f, 0.5f, sin(theta) * 0.5f);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();
}