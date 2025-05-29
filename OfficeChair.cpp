#include "OfficeChair.h"
#include "GL/glut.h"

OfficeChair::OfficeChair() {
    x = y = z = 0.0f;
    width = 0.5f; height = 0.1f; depth = 0.5f; // Kích thước mặt ngồi
    backHeight = 0.5f;                         // Chiều cao lưng ghế
    rotationAngle = 0.0f;
    isRotating = false;
    bodyColor[0] = 0.2f; bodyColor[1] = 0.2f; bodyColor[2] = 0.2f; // Màu xám đậm
    legColor[0] = 0.4f; legColor[1] = 0.4f; legColor[2] = 0.4f;   // Màu xám sáng
}

void OfficeChair::setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void OfficeChair::setSize(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
}

void OfficeChair::setBackHeight(float h) {
    backHeight = h;
}

void OfficeChair::setBodyColor(float r, float g, float b) {
    bodyColor[0] = r;
    bodyColor[1] = g;
    bodyColor[2] = b;
}

void OfficeChair::setLegColor(float r, float g, float b) {
    legColor[0] = r;
    legColor[1] = g;
    legColor[2] = b;
}

void OfficeChair::toggleRotate() {
    isRotating = !isRotating;
}

void OfficeChair::updateRotation() {
    if (isRotating) {
        rotationAngle += 1.0f; // Tốc độ xoay
        if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
    }
}

void OfficeChair::draw() const {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Xoay quanh trục Y

    // Vẽ mặt ngồi
    glColor3fv(bodyColor);
    glBegin(GL_QUADS);
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

    // Vẽ lưng ghế
    glBegin(GL_QUADS);
    // Mặt trước lưng ghế
    glNormal3f(0, 0, 1);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glVertex3f(width / 2, height / 2 + backHeight, -depth / 2);
    glVertex3f(-width / 2, height / 2 + backHeight, -depth / 2);
    // Mặt sau lưng ghế
    glNormal3f(0, 0, -1);
    glVertex3f(-width / 2, height / 2, -depth / 2 - 0.05f);
    glVertex3f(width / 2, height / 2, -depth / 2 - 0.05f);
    glVertex3f(width / 2, height / 2 + backHeight, -depth / 2 - 0.05f);
    glVertex3f(-width / 2, height / 2 + backHeight, -depth / 2 - 0.05f);
    // Mặt trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-width / 2, height / 2, -depth / 2 - 0.05f);
    glVertex3f(-width / 2, height / 2 + backHeight, -depth / 2 - 0.05f);
    glVertex3f(-width / 2, height / 2 + backHeight, -depth / 2);
    glVertex3f(-width / 2, height / 2, -depth / 2);
    // Mặt phải
    glNormal3f(1, 0, 0);
    glVertex3f(width / 2, height / 2, -depth / 2 - 0.05f);
    glVertex3f(width / 2, height / 2 + backHeight, -depth / 2 - 0.05f);
    glVertex3f(width / 2, height / 2 + backHeight, -depth / 2);
    glVertex3f(width / 2, height / 2, -depth / 2);
    glEnd();

    // Vẽ chân ghế (trụ chính)
    glColor3fv(legColor);
    glPushMatrix();
    glTranslatef(0.0f, -height / 2 - 0.2f, 0.0f); // Trụ dưới mặt ngồi
    glScalef(0.05f, 0.2f, 0.05f); // Trụ mỏng, cao 0.2
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ 4 bánh xe (hình cầu nhỏ)
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glColor3fv(legColor);
    float wheelOffset = 0.2f; // Khoảng cách bánh xe từ tâm
    float wheelY = -height / 2 - 0.4f; // Vị trí bánh xe dưới sàn
    // Bánh xe 1
    glPushMatrix();
    glTranslatef(wheelOffset, wheelY, wheelOffset);
    glutSolidSphere(0.03f, 10, 10);
    glPopMatrix();
    // Bánh xe 2
    glPushMatrix();
    glTranslatef(-wheelOffset, wheelY, wheelOffset);
    glutSolidSphere(0.03f, 10, 10);
    glPopMatrix();
    // Bánh xe 3
    glPushMatrix();
    glTranslatef(wheelOffset, wheelY, -wheelOffset);
    glutSolidSphere(0.03f, 10, 10);
    glPopMatrix();
    // Bánh xe 4
    glPushMatrix();
    glTranslatef(-wheelOffset, wheelY, -wheelOffset);
    glutSolidSphere(0.03f, 10, 10);
    glPopMatrix();
    glPopAttrib();

    glPopMatrix();
}