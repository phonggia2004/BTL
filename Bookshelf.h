#ifndef BOOKSHELF_H
#define BOOKSHELF_H

class Bookshelf {
private:
    float x, y, z;          // Vị trí tủ sách
    float width, height, depth; // Kích thước tủ
    float color[3];         // Màu tủ
    int numShelves;         // Số ngăn
    float bookColors[3][3]; // Màu của sách (3 màu khác nhau)

public:
    Bookshelf();
    void setPosition(float x, float y, float z);
    void setSize(float w, float h, float d);
    void setColor(float r, float g, float b);
    void draw() const;
};

#endif