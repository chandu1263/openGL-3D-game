#include "pyramid.h"
#include "main.h"

Pyramid::Pyramid(float x, float y, float z, float b, float l, float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    //this->values = glm::vec3(b,l,h);
    //this->rotation = 0;
    const GLfloat vertex_buffer_data[] = {
      //flatsurface
      0,b,0,
      l,0,0,
      -l,0,0,
      //2
      -l,0,0,
      0,-b,0,
      l,0,0,
      //lateralside1
      0,b,0,
      l,0,0,
      0,0,h,
      //lateralside2
      0,b,0,
      -l,0,0,
      0,0,h,
      //lateralside3
      0,-b,0,
      l,0,0,
      0,0,h,
      //lateralside4
      -l,0,0,
      0,-b,0,
      0,0,h
   };

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Pyramid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pyramid::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Pyramid::tick() {
   // this->rotation += speed;
    //this->position.x += speedx;
    //this->position.y += speedy;
    //this->position.z +=speedz;
  }
  bounding_box_t Pyramid::bounding_box() {
    float x = this->position.x, y = this->position.y;
    //float b = this->values.b, l = this->values.l;
    bounding_box_t bbox = { x, y};
    return bbox;
}
