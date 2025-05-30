#include <GL/glut.h>
#include "Car.h"
#include <cmath>

Car::Car() {
    colorR = 0.0f;
    colorG = 0.0f;
    colorB = 1.0f; // Màu mặc định xanh dương
}

void Car::setColor(float r, float g, float b) {
    colorR = r;
    colorG = g;
    colorB = b;
}

void Car::drawBox(float w, float h, float d) {
    glBegin(GL_QUADS);
    // mặt trước
    glNormal3f(0, 0, 1);
    glVertex3f(-w / 2, 0, d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(-w / 2, h, d / 2);

    // mặt sau
    glNormal3f(0, 0, -1);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, h, -d / 2);
    glVertex3f(-w / 2, h, -d / 2);

    // mặt bên phải
    glNormal3f(1, 0, 0);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(w / 2, h, -d / 2);

    // mặt bên trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(-w / 2, 0, d / 2);
    glVertex3f(-w / 2, h, d / 2);
    glVertex3f(-w / 2, h, -d / 2);

    // mặt trên
    glNormal3f(0, 1, 0);
    glVertex3f(-w / 2, h, -d / 2);
    glVertex3f(w / 2, h, -d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(-w / 2, h, d / 2);

    // mặt dưới
    glNormal3f(0, -1, 0);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(-w / 2, 0, d / 2);
    glEnd();
}

void Car::drawCylinder(float radius, float height) {
    const int slices = 20;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; i++) {
        float theta = (2.0f * 3.1415926f * i) / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glNormal3f(cos(theta), 0, sin(theta));
        glVertex3f(x, 0, z);
        glVertex3f(x, height, z);
    }
    glEnd();

    // Đáy
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0);
    for (int i = 0; i <= slices; i++) {
        float theta = (2.0f * 3.1415926f * i) / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, 0, z);
    }
    glEnd();

    // Đỉnh
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glVertex3f(0, height, 0);
    for (int i = 0; i <= slices; i++) {
        float theta = (2.0f * 3.1415926f * i) / slices;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, height, z);
    }
    glEnd();
}

void Car::draw() {
    glColor3f(colorR, colorG, colorB);

    // Vẽ thân xe (hình hộp)
    glPushMatrix();
    glTranslatef(0, 0.3f, 0);
    drawBox(2.0f, 0.5f, 1.0f);
    glPopMatrix();

    // Vẽ cabin (hình hộp nhỏ hơn)
    glPushMatrix();
    glTranslatef(0.2f, 0.8f, 0);
    drawBox(1.0f, 0.4f, 1.0f);
    glPopMatrix();

    // Vẽ bánh xe (4 bánh nằm bên hông)
    float wheelRadius = 0.25f;
    float wheelWidth = 0.2f;
    float wheelX = 1.1f;     // vị trí hai bên hông
    float wheelY = 0.15f;
    float wheelZ = 0.5f;     // trước/sau

    for (int side = -1; side <= 1; side += 2) {     // trái/phải
        for (int front = -1; front <= 1; front += 2) { // trước/sau
            glPushMatrix();
            glTranslatef(side * wheelX, wheelY, front * wheelZ);

            glRotatef(90, 1, 0, 0);

            drawCylinder(wheelRadius, wheelWidth);
            glPopMatrix();
        }
    }

}
