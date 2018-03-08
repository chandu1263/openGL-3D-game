#include "main.h"
#include "cube.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, float b, float l, float h, color_t color);
    glm::vec3 position;
    float rotation;
    float speedx;
     float speedy;
     int view;
     Cube cannon;
     Cube cannontop;
    // float speedz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object,*object1,*object2;

};

#endif // BOAT_H
