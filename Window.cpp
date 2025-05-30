#include <GL/glut.h>
#include "Window.h"

void Window::draw() {
    // Vị trí cửa sổ ở tường trước (z = 4.9f)
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 4.9f); // Dịch đến tường trước
    glScalef(1.2f, 1.2f, 0.1f);     // Kích thước khung (đảo X và Z)
    glColor3f(0.6f, 0.6f, 0.6f);    // Màu khung
    glutSolidCube(1.0f);            // Khung cửa sổ
    glPopMatrix();

    // Kính trong suốt (mô phỏng bằng màu xanh nhạt và alpha)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 0.8f, 1.0f, 0.3f); // Kính mờ

    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 4.85f);  // Dịch sát khung (hơi nhô ra ngoài)
    glScalef(1.0f, 1.0f, 0.01f);      // Kích thước kính
    glutSolidCube(1.0f);
    glPopMatrix();

    glDisable(GL_BLEND);
}