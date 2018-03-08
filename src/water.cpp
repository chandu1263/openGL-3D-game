#include "water.h"
#include "main.h"

Water::Water(float x, float y,float z, color_t color){
  this->position = glm::vec3(x,y,z);
  this->rotation = 0;
  this->box = Cube(x,y,z,1000,1000,2,color);
  // this->box.speedx=0;
  // this->box.speedy=0;
  // this->box.speedz=0;

}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    box.draw(MVP);
}
void Water::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Water::tick() {
    this->rotation += speed;

}
