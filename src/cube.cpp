#include "cube.h"
#include "main.h"
float ll,bb,hh;
Cube::Cube(float x, float y, float z, float b, float l, float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // this->speedx=0;
    // this->speedy=0;
    // this->speedz=0;
    ll=l/2;
    bb=b/2;
    hh=h/2;
    const GLfloat vertex_buffer_data[] = {
        //topside
        //triangle1
        // 0,0,h,
        // l,0,b,
        // l,b,h,
        -ll, bb, -hh,
        -ll, bb, hh,
        ll, bb, -hh,
        // //triangle2
        // 0,0,h,
        // l,b,h,
        // 0,b,h,
        ll, bb, -hh,
        -ll, bb, hh,
        ll, bb, hh,
        // //lateralside1
        // //triangle3
        // l,0,b,
        // l,0,0,
        // l,b,h,
        -ll, bb, hh,
        ll, bb, hh,
        -ll, -bb, hh,
        // //triangle4
        // l,b,h,
        // l,0,0,
        // l,b,0,
        -ll, -bb, hh,
        ll, bb, hh,
        ll, -bb, hh,
        // //lateralside2
        // //triangle5
        // l,b,h,
        // l,b,0,
        // 0,b,0,
        -ll, bb, -hh,
        ll, bb, -hh,
        -ll, -bb, -hh,

        // //triangle6
        // 0,b,0,
        // 0,b,h, //OBH :P
        // l,b,h,
        -ll, -bb, -hh,
        ll, bb, -hh,
        ll, -bb, -hh,
        // //lateralside3
        // //triangle7
        // 0,b,0,
        // 0,b,h,
        // 0,0,h,
        -ll, bb, -hh,
        -ll, -bb, -hh,
        -ll, bb, hh,
        // //triangle8
        // 0,0,h,
        // 0,b,0,
        // 0,0,0,
        -ll, bb, hh,
        -ll,-bb, -hh,
        -ll, -bb, hh,
        // //lateralside4
        // //triangle9
        // 0,0,h,
        // 0,0,0,
        // l,0,b,
        ll, bb, -hh,
        ll, -bb, -hh,
        ll, bb, hh,
        // //triangle10
        // 0,0,0,
        // l,0,b,
        // l,0,0,
        ll, bb, hh,
        ll,-bb, -hh,
        ll, -bb, hh,
        // //downside
        // //triangle11
        // 0,0,0,
        // l,0,0,
        // 0,b,0,
        -ll, -bb, -hh,
        -ll, -bb, hh,
        ll, -bb, -hh,
        // //triangle12
        // l,b,0,
        // l,0,0,
        // 0,b,0
        ll, -bb, -hh,
        -ll, -bb, hh,
        ll, -bb, hh


   };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cube::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cube::tick() {
   // this->rotation += speed;
    // this->position.x += speedx;
    // this->position.y += speedy;
    // this->position.z +=speedz;
  }
