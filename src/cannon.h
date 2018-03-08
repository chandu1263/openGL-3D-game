#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, float b, float l, float h, color_t color);
    glm::vec3 position;
    float rotation;
    // float speedx;
    // float speedy;
    // float speedz;
    float theeta;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // CANNON_H
