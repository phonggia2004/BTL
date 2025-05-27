#pragma once
#ifndef SPEAKER_H
#define SPEAKER_H

class Speaker {
public:
    Speaker();
    Speaker(float x, float y, float z); // Constructor với tham số
    void setPosition(float x, float y, float z);
    void setScale(float scale);
    void setRotation(float angle);
    void draw();

private:
    float x, y, z;
    float scale;
    float rotation;
};

// Hàm drawSpeaker độc lập
void drawspeaker(float x, float y, float z, float scale, float rotation);

#endif