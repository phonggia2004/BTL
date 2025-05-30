#include "Bookshelf.h"
#include "GL/glut.h"
#include <cstdlib>
#include <cstdio> 
#include <ctime>

Bookshelf::Bookshelf() {
    x = y = z = 0.0f;
    width = 1.0f; height = 2.0f; depth = 0.4f;
    numShelves = 3;
    thickness = 0.05f; // Định nghĩa độ dày cố định
    // Màu gỗ cơ bản
    color[0] = 0.6f; color[1] = 0.3f; color[2] = 0.1f;

    // Màu sách đơn giản
    bookColors[0][0] = 0.8f; bookColors[0][1] = 0.2f; bookColors[0][2] = 0.2f; // Đỏ
    bookColors[1][0] = 0.2f; bookColors[1][1] = 0.2f; bookColors[1][2] = 0.8f; // Xanh dương
    bookColors[2][0] = 0.2f; bookColors[2][1] = 0.8f; bookColors[2][2] = 0.2f; // Xanh lá
    bookColors[3][0] = 0.9f; bookColors[3][1] = 0.6f; bookColors[3][2] = 0.0f; // Cam

    srand(time(NULL));
}

void Bookshelf::setPosition(float x, float y, float z) {
    this->x = x; this->y = y; this->z = z;
}

void Bookshelf::setSize(float w, float h, float d) {
    if (w <= 0 || h <= 0 || d <= 0) return; 
    width = w; height = h; depth = d;
    shelfHeight = (height - 2 * thickness) / numShelves; // Tính lại shelfHeight khi kích thước thay đổi
}

void Bookshelf::setColor(float r, float g, float b) {
    color[0] = (r > 1.0f) ? 1.0f : (r < 0.0f) ? 0.0f : r;
    color[1] = (g > 1.0f) ? 1.0f : (g < 0.0f) ? 0.0f : g;
    color[2] = (b > 1.0f) ? 1.0f : (b < 0.0f) ? 0.0f : b;
}

void Bookshelf::setNumShelves(int n) {
    if (n <= 0) n = 1; 
    numShelves = n;
    shelfHeight = (height - 2 * thickness) / numShelves; // Cập nhật shelfHeight
}

void Bookshelf::drawBox(float w, float h, float d) const {
    glBegin(GL_QUADS);


    // Mặt sau
    glNormal3f(0, 0, -1);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(-w / 2, h, -d / 2);
    glVertex3f(w / 2, h, -d / 2);
    glVertex3f(w / 2, 0, -d / 2);

    // Mặt trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(-w / 2, 0, d / 2);
    glVertex3f(-w / 2, h, d / 2);
    glVertex3f(-w / 2, h, -d / 2);

    // Mặt phải
    glNormal3f(1, 0, 0);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, h, -d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(w / 2, 0, d / 2);

    // Mặt trên
    glNormal3f(0, 1, 0);
    glVertex3f(-w / 2, h, -d / 2);
    glVertex3f(-w / 2, h, d / 2);
    glVertex3f(w / 2, h, d / 2);
    glVertex3f(w / 2, h, -d / 2);

    // Mặt dưới
    glNormal3f(0, -1, 0);
    glVertex3f(-w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, -d / 2);
    glVertex3f(w / 2, 0, d / 2);
    glVertex3f(-w / 2, 0, d / 2);

    glEnd();
}

void Bookshelf::draw() const {
    glPushMatrix();
    glTranslatef(x, y, z); // Đặt vị trí kệ theo setPosition

    // Vẽ khung kệ
    glColor3fv(color);
    drawBox(width, height, depth);

    // Vẽ các tầng kệ
    float usableHeight = height - 2 * thickness; // Chiều cao có thể sử dụng
    for (int i = 0; i < numShelves; i++) {
        glPushMatrix();
        float layerY = y + thickness + i * (usableHeight / numShelves); // Căn chỉnh với y và chiều cao sử dụng
        glTranslatef(0, layerY, 0); // Dịch từ vị trí y của kệ
        drawBox(width - 2 * thickness, thickness, depth - thickness);
        glPopMatrix();

        // Vẽ sách trên mỗi tầng
        int booksPerShelf = 4;
        float bookSpacing = (width - 2 * thickness) / booksPerShelf;
        for (int j = 0; j < booksPerShelf; j++) {
            int colorIndex = (i * booksPerShelf + j) % 4;
            glColor3fv(bookColors[colorIndex]);

            float bookWidth = 0.08f + (rand() % 3) * 0.01f;
            float bookHeight = (usableHeight / numShelves) * 0.8f; // Sử dụng chiều cao tầng
            float bookDepth = depth * 0.6f;

            glPushMatrix();
            float bookY = y + thickness + i * (usableHeight / numShelves); // Căn giữa với tầng
            glTranslatef(-width / 2 + thickness + j * bookSpacing + bookSpacing / 2, bookY, 0);
            drawBox(bookWidth, bookHeight, bookDepth);
            glPopMatrix();
        }
    }

    glPopMatrix();
}