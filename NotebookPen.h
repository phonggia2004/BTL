#ifndef NOTEBOOKPEN_H
#define NOTEBOOKPEN_H

#include <GL/glut.h>

class NotebookPen {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ; 
    float angleX, angleY, angleZ; 
    float pageColorR, pageColorG, pageColorB; 
    float coverColorR, coverColorG, coverColorB; 
    float penColorR, penColorG, penColorB; 

public:
    NotebookPen();


    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setPageColor(float r, float g, float b);
    void setCoverColor(float r, float g, float b);
    void setPenColor(float r, float g, float b);

 
    void draw();
};

#endif