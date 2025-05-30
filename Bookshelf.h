#ifndef BOOKSHELF_H
#define BOOKSHELF_H

class Bookshelf {
public:
    Bookshelf();
    void setPosition(float x, float y, float z);
    void setSize(float w, float h, float d);
    void setColor(float r, float g, float b);
    void setNumShelves(int n); 
    void draw() const;

private:
    float x, y, z;
    float width, height, depth;
    int numShelves;
    float thickness; 
    float shelfHeight; 
    float color[3];
    float bookColors[4][3]; 

    void drawBox(float w, float h, float d) const;
};

#endif