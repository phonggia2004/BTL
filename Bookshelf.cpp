#include "Bookshelf.h"
#include "GL/glut.h"

Bookshelf::Bookshelf() {
    x = y = z = 0.0f;
    width = 1.0f; height = 2.0f; depth = 0.4f; // Kích thước tủ
    numShelves = 3; // 3 ngăn
    color[0] = 0.6f; color[1] = 0.3f; color[2] = 0.1f; // Màu gỗ nâu
    // Màu sách: đỏ, xanh dương, xanh lá
    bookColors[0][0] = 0.8f; bookColors[0][1] = 0.2f; bookColors[0][2] = 0.2f; // Đỏ
    bookColors[1][0] = 0.2f; bookColors[1][1] = 0.2f; bookColors[1][2] = 0.8f; // Xanh dương
    bookColors[2][0] = 0.2f; bookColors[2][1] = 0.8f; bookColors[2][2] = 0.2f; // Xanh lá
}

void Bookshelf::setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Bookshelf::setSize(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
}

void Bookshelf::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Bookshelf::draw() const {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3fv(color);

    // Vẽ khung ngoài của tủ
    glBegin(GL_QUADS);
    // Mặt sau
    glNormal3f(0, 0, 1);
    glVertex3f(-width / 2, 0, -depth / 2);
    glVertex3f(width / 2, 0, -depth / 2);
    glVertex3f(width / 2, height, -depth / 2);
    glVertex3f(-width / 2, height, -depth / 2);
    // Mặt trái
    glNormal3f(-1, 0, 0);
    glVertex3f(-width / 2, 0, -depth / 2);
    glVertex3f(-width / 2, height, -depth / 2);
    glVertex3f(-width / 2, height, depth / 2);
    glVertex3f(-width / 2, 0, depth / 2);
    // Mặt phải
    glNormal3f(1, 0, 0);
    glVertex3f(width / 2, 0, -depth / 2);
    glVertex3f(width / 2, height, -depth / 2);
    glVertex3f(width / 2, height, depth / 2);
    glVertex3f(width / 2, 0, depth / 2);
    // Mặt dưới
    glNormal3f(0, -1, 0);
    glVertex3f(-width / 2, 0, -depth / 2);
    glVertex3f(width / 2, 0, -depth / 2);
    glVertex3f(width / 2, 0, depth / 2);
    glVertex3f(-width / 2, 0, depth / 2);
    // Mặt trên
    glNormal3f(0, 1, 0);
    glVertex3f(-width / 2, height, -depth / 2);
    glVertex3f(width / 2, height, -depth / 2);
    glVertex3f(width / 2, height, depth / 2);
    glVertex3f(-width / 2, height, depth / 2);
    glEnd();

    // Vẽ các ngăn
    float shelfHeight = height / (numShelves + 1);
    for (int i = 1; i <= numShelves; i++) {
        glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-width / 2, i * shelfHeight, -depth / 2);
        glVertex3f(width / 2, i * shelfHeight, -depth / 2);
        glVertex3f(width / 2, i * shelfHeight, depth / 2);
        glVertex3f(-width / 2, i * shelfHeight, depth / 2);
        glEnd();

        // Vẽ sách trên mỗi ngăn
        float bookWidth = 0.1f, bookHeight = shelfHeight * 0.8f, bookDepth = depth * 0.8f;
        int booksPerShelf = 3; // 3 cuốn sách mỗi ngăn
        for (int j = 0; j < booksPerShelf; j++) {
            glPushMatrix();
            glTranslatef(-width / 2 + (j + 0.5f) * (width / booksPerShelf), i * shelfHeight, 0);
            glColor3fv(bookColors[j % 3]); // Chọn màu sách theo vòng lặp
            glBegin(GL_QUADS);
            // Mặt trước sách
            glNormal3f(0, 0, -1);
            glVertex3f(-bookWidth / 2, 0, bookDepth / 2);
            glVertex3f(bookWidth / 2, 0, bookDepth / 2);
            glVertex3f(bookWidth / 2, bookHeight, bookDepth / 2);
            glVertex3f(-bookWidth / 2, bookHeight, bookDepth / 2);
            // Mặt sau sách
            glNormal3f(0, 0, 1);
            glVertex3f(-bookWidth / 2, 0, -bookDepth / 2);
            glVertex3f(bookWidth / 2, 0, -bookDepth / 2);
            glVertex3f(bookWidth / 2, bookHeight, -bookDepth / 2);
            glVertex3f(-bookWidth / 2, bookHeight, -bookDepth / 2);
            // Mặt trái
            glNormal3f(-1, 0, 0);
            glVertex3f(-bookWidth / 2, 0, -bookDepth / 2);
            glVertex3f(-bookWidth / 2, bookHeight, -bookDepth / 2);
            glVertex3f(-bookWidth / 2, bookHeight, bookDepth / 2);
            glVertex3f(-bookWidth / 2, 0, bookDepth / 2);
            // Mặt phải
            glNormal3f(1, 0, 0);
            glVertex3f(bookWidth / 2, 0, -bookDepth / 2);
            glVertex3f(bookWidth / 2, bookHeight, -bookDepth / 2);
            glVertex3f(bookWidth / 2, bookHeight, bookDepth / 2);
            glVertex3f(bookWidth / 2, 0, bookDepth / 2);
            // Mặt trên
            glNormal3f(0, 1, 0);
            glVertex3f(-bookWidth / 2, bookHeight, -bookDepth / 2);
            glVertex3f(bookWidth / 2, bookHeight, -bookDepth / 2);
            glVertex3f(bookWidth / 2, bookHeight, bookDepth / 2);
            glVertex3f(-bookWidth / 2, bookHeight, bookDepth / 2);
            glEnd();
            glPopMatrix();
        }
    }
    glPopMatrix();
}