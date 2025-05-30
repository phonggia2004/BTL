#include "NotebookPen.h"
#include <cmath>

NotebookPen::NotebookPen() {
    posX = posY = posZ = 0.0f;
    scaleX = scaleY = scaleZ = 1.0f;
    angleX = angleY = angleZ = 0.0f;
    pageColorR = 1.0f; pageColorG = 1.0f; pageColorB = 1.0f; // Màu trắng cho trang giấy
    coverColorR = 0.0f; coverColorG = 0.0f; coverColorB = 0.5f; // Màu xanh đậm cho bìa
    penColorR = 0.0f; penColorG = 0.0f; penColorB = 0.0f; // Màu đen cho bút
}

void NotebookPen::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void NotebookPen::setScale(float sx, float sy, float sz) {
    scaleX = sx;
    scaleY = sy;
    scaleZ = sz;
}

void NotebookPen::setRotation(float ax, float ay, float az) {
    angleX = ax;
    angleY = ay;
    angleZ = az;
}

void NotebookPen::setPageColor(float r, float g, float b) {
    pageColorR = r;
    pageColorG = g;
    pageColorB = b;
}

void NotebookPen::setCoverColor(float r, float g, float b) {
    coverColorR = r;
    coverColorG = g;
    coverColorB = b;
}

void NotebookPen::setPenColor(float r, float g, float b) {
    penColorR = r;
    penColorG = g;
    penColorB = b;
}

void NotebookPen::draw() {
    glPushMatrix();
    // Áp dụng các phép biến đổi
    glTranslatef(posX, posY, posZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);

    // Vẽ quyển vở (phần trang giấy)
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f); // Đặt quyển vở ở y = 0.05 để bìa ở dưới
    glScalef(0.4f, 0.01f, 0.3f); // Kích thước: 0.4m (rộng) x 0.01m (dày) x 0.3m (dài)
    glColor3f(pageColorR, pageColorG, pageColorB);
    glBegin(GL_QUADS);
    // Mặt trên
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // Mặt dưới
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // Mặt trước
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // Mặt sau
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // Mặt trái
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    // Mặt phải
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
    glPopMatrix();

    // Vẽ bìa vở (phía dưới trang giấy)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Đặt bìa ngay dưới trang giấy
    glScalef(0.4f, 0.01f, 0.3f); // Kích thước: 0.4m (rộng) x 0.01m (dày) x 0.3m (dài)
    glColor3f(coverColorR, coverColorG, coverColorB);
    glBegin(GL_QUADS);
    // Mặt trên
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // Mặt dưới
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // Mặt trước
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // Mặt sau
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // Mặt trái
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    // Mặt phải
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
    glPopMatrix();

    // Vẽ bút (hình trụ đơn giản)
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.15f); // Đặt bút trên quyển vở, nghiêng một chút
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Nghiêng bút để trông tự nhiên
    glScalef(0.05f, 0.05f, 0.3f); // Kích thước: 0.05m (bán kính) x 0.3m (dài)
    int sides = 20;
    glColor3f(penColorR, penColorG, penColorB);
    for (int i = 0; i < sides; i++) {
        float theta1 = (2.0f * 3.14159f * i) / sides;
        float theta2 = (2.0f * 3.14159f * (i + 1)) / sides;
        glBegin(GL_QUADS);
        // Mặt bên
        glNormal3f(cos(theta1), sin(theta1), 0.0f);
        glVertex3f(cos(theta1) * 0.5f, sin(theta1) * 0.5f, -0.5f);
        glVertex3f(cos(theta2) * 0.5f, sin(theta2) * 0.5f, -0.5f);
        glVertex3f(cos(theta2) * 0.5f, sin(theta2) * 0.5f, 0.5f);
        glVertex3f(cos(theta1) * 0.5f, sin(theta1) * 0.5f, 0.5f);
        glEnd();
    }
    // Mặt trên và mặt dưới (đầu bút và đuôi bút)
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    for (int i = 0; i < sides; i++) {
        float theta = (2.0f * 3.14159f * i) / sides;
        glVertex3f(cos(theta) * 0.5f, sin(theta) * 0.5f, -0.5f);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < sides; i++) {
        float theta = (2.0f * 3.14159f * i) / sides;
        glVertex3f(cos(theta) * 0.5f, sin(theta) * 0.5f, 0.5f);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();
}