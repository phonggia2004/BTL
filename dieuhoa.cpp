#include "dieuhoa.h"
#include "GL/glut.h"

AirConditioner::AirConditioner() {
    x = y = z = 0.0f;
    width = 1.0f; height = 0.4f; depth = 0.2f;
    isOn = false;
    bodyColor[0] = 0.9f; bodyColor[1] = 0.9f; bodyColor[2] = 0.9f; // Màu trắng xám
    ventColor[0] = 0.3f; ventColor[1] = 0.3f; ventColor[2] = 0.3f; // Màu xám đậm
}

void AirConditioner::setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void AirConditioner::setSize(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
}

void AirConditioner::setBodyColor(float r, float g, float b) {
    bodyColor[0] = r;
    bodyColor[1] = g;
    bodyColor[2] = b;
}

void AirConditioner::setVentColor(float r, float g, float b) {
    ventColor[0] = r;
    ventColor[1] = g;
    ventColor[2] = b;
}

void AirConditioner::turnOn() {
    isOn = true;
}

void AirConditioner::turnOff() {
    isOn = false;
}

bool AirConditioner::getState() const {
    return isOn;
}

void AirConditioner::draw() const {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Vẽ thân điều hòa
    glColor3fv(bodyColor);
    glBegin(GL_QUADS);
    // Mặt trước
    glNormal3f(0, 0, 1);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    // Mặt sau
    glNormal3f(0, 0, -1);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    // Mặt trên
    glNormal3f(0, 1, 0);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    // Mặt dưới
    glNormal3f(0, -1, 0);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    // Mặt trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-width / 2, -height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(-width / 2, height / 2, depth / 2);
    glVertex3f(-width / 2, -height / 2, depth / 2);
    // Mặt phải
    glNormal3f(1, 0, 0);
    glVertex3f(width / 2, -height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, depth / 2);
    glVertex3f(width / 2, -height / 2, depth / 2);
    glEnd();

    // Vẽ khe gió (mặt trước, phía dưới)
    glColor3fv(ventColor);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-width / 2 + 0.1f, -height / 2 + 0.05f, depth / 2 + 0.01f);
    glVertex3f(width / 2 - 0.1f, -height / 2 + 0.05f, depth / 2 + 0.01f);
    glVertex3f(width / 2 - 0.1f, -height / 2 + 0.15f, depth / 2 + 0.01f);
    glVertex3f(-width / 2 + 0.1f, -height / 2 + 0.15f, depth / 2 + 0.01f);
    glEnd();

    // Hiệu ứng khi điều hòa bật (đèn nhỏ màu xanh)
    if (isOn) {
        glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glColor3f(0.0f, 1.0f, 0.0f); // Màu xanh lá
        glPushMatrix();
        glTranslatef(width / 2 - 0.1f, -height / 2 + 0.1f, depth / 2 + 0.02f);
        glutSolidSphere(0.03f, 10, 10);
        glPopMatrix();
        glPopAttrib();
    }

    glPopMatrix();
}