#include <GL/glut.h>
#include "tudungdo.h"

void drawCube(float width, float height, float depth) {
    // Vẽ 1 hình hộp chữ nhật
    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    glBegin(GL_QUADS);
    // mặt trước
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);

    // mặt sau
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);

    // mặt trái
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);

    // mặt phải
    glVertex3f(w, -h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, h, d);
    glVertex3f(w, -h, d);

    // mặt trên
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);

    // mặt dưới
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);
    glEnd();
}

void drawWardrobe() {
    // màu xám
    glColor3f(0.5f, 0.5f, 0.5f);

    // thân tủ
    drawCube(2.0f, 3.0f, 1.0f);

    // tay nắm cửa (hình chữ nhật nhỏ màu tối hơn)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.9f, 0.0f, 0.55f);
    drawCube(0.1f, 0.5f, 0.1f);
    glPopMatrix();

    // chia cửa tủ 2 bên (vẽ thêm 1 đường kẻ)
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -1.5f, 0.51f);
    glVertex3f(0.0f, 1.5f, 0.51f);
    glEnd();
}
