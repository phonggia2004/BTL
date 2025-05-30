#include "Door.h"
#include "GL/glut.h"

Door::Door() {
    posX = posY = posZ = 0.0f;
    scaleX = scaleY = scaleZ = 1.0f;
    angleX = angleY = angleZ = 0.0f;
    colorR = 0.6f; colorG = 0.3f; colorB = 0.1f; // Màu gỗ mặc định
    handleColorR = 0.7f; handleColorG = 0.7f; handleColorB = 0.7f; // Màu tay nắm bạc
    isOpen = false;
}

void Door::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Door::setScale(float sx, float sy, float sz) {
    scaleX = sx;
    scaleY = sy;
    scaleZ = sz;
}

void Door::setRotation(float ax, float ay, float az) {
    angleX = ax;
    angleY = ay;
    angleZ = az;
}

void Door::setColor(float r, float g, float b) {
    colorR = r;
    colorG = g;
    colorB = b;
}

void Door::setHandleColor(float r, float g, float b) {
    handleColorR = r;
    handleColorG = g;
    handleColorB = b;
}

void Door::open() {
    isOpen = true;
}

void Door::close() {
    isOpen = false;
}

bool Door::getState() const {
    return isOpen;
}

void Door::draw() {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);
    if (isOpen) {
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Xoay 90 độ quanh trục Y để mở cửa
    }

    // Vẽ thân cửa
    glBegin(GL_QUADS);
    glColor3f(colorR, colorG, colorB);
    // Mặt trước
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.5f, 0.0f, -0.05f);
    glVertex3f(0.5f, 0.0f, -0.05f);
    glVertex3f(0.5f, 2.0f, -0.05f);
    glVertex3f(-0.5f, 2.0f, -0.05f);
    // Mặt sau
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.0f, 0.05f);
    glVertex3f(-0.5f, 2.0f, 0.05f);
    glVertex3f(0.5f, 2.0f, 0.05f);
    glVertex3f(0.5f, 0.0f, 0.05f);
    // Mặt bên trái
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, -0.05f);
    glVertex3f(-0.5f, 2.0f, -0.05f);
    glVertex3f(-0.5f, 2.0f, 0.05f);
    glVertex3f(-0.5f, 0.0f, 0.05f);
    // Mặt bên phải
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, -0.05f);
    glVertex3f(0.5f, 0.0f, 0.05f);
    glVertex3f(0.5f, 2.0f, 0.05f);
    glVertex3f(0.5f, 2.0f, -0.05f);
    // Mặt dưới
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, -0.05f);
    glVertex3f(0.5f, 0.0f, -0.05f);
    glVertex3f(0.5f, 0.0f, 0.05f);
    glVertex3f(-0.5f, 0.0f, 0.05f);
    // Mặt trên
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 2.0f, -0.05f);
    glVertex3f(-0.5f, 2.0f, 0.05f);
    glVertex3f(0.5f, 2.0f, 0.05f);
    glVertex3f(0.5f, 2.0f, -0.05f);
    glEnd();

    // Vẽ tay nắm cửa
    glPushMatrix();
    glTranslatef(0.3f, 1.0f, -0.06f);
    glColor3f(handleColorR, handleColorG, handleColorB);
    glutSolidSphere(0.15f, 20, 20);
    glPopMatrix();

    glPopMatrix();
}