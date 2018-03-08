#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float speedx;
     float speedy;
     int appear;
    // float speedz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object,*object1,*object2;

};

#endif // MONSTER_H
