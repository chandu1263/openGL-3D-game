#include "main.h"
#include "cube.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float theeta;
    Cube gun;
    // float speedx;
    // float speedy;
    // float speedz;
    //float theeta;
    Cube cannon1;
    Cube cannontop;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // CANNON_H
