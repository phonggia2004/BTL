#ifndef SHELF_H
#define SHELF_H

class Shelf {
public:
    Shelf();
    void setSize(float width, float height, float depth);
    void setColor(float r, float g, float b);
    void draw();

private:
    float width, height, depth;
    float colorR, colorG, colorB;

    void drawBox(float w, float h, float d);
};

#endif
