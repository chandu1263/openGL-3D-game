#include "main.h"

#ifndef PYRAMID_H
#define PYRAMID_H


class Pyramid {
public:
    Pyramid() {}
    Pyramid(float x, float y, float z, float b, float l, float h, color_t color);
    glm::vec3 position;
    //glm::vec3 values;
     float rotation;
    // float speedx;
    // float speedy;
    // float speedz;
    int appear;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // PYRAMID_H
