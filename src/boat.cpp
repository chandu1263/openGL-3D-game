#include "boat.h"
#include "main.h"
#include "cube.h"
float ll1,bb1,hh1;
Boat::Boat(float x, float y, float z, float b, float l, float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedx=0;
    // this->speedy=0;
   this->speedy=0;
    ll1=l/2;
    bb1=b/2;
    hh1=h/2;
    const GLfloat vertex_buffer_data[] = {
        //topside
        //triangle1
        // 0,0,h,
        // l,0,b,
        // l,b,h,
        -ll1/2, bb1/2, -hh1/2,
        -ll1, bb1, hh1,
        ll1/2, bb1/2, -hh1/2,
        // //triangle2
        // 0,0,h,
        // l,b,h,
        // 0,b,h,
        ll1/2, bb1/2, -hh1/2,
        -ll1, bb1, hh1,
        ll1, bb1, hh1,
        // //lateralside1
        // //triangle3
        // l,0,b,
        // l,0,0,
        // l,b,h,
        -ll1, bb1, hh1,
        ll1, bb1, hh1,
        -ll1, -bb1, hh1,
        // //triangle4
        // l,b,h,
        // l,0,0,
        // l,b,0,
        -ll1, -bb1, hh1,
        ll1, bb1, hh1,
        ll1, -bb1, hh1,
        // //lateralside2
        // //triangle5
        // l,b,h,
        // l,b,0,
        // 0,b,0,
        -ll1/2, bb1/2, -hh1/2,
        ll1/2, bb1/2, -hh1/2,
        -ll1/2, -bb1/2, -hh1/2,

        // //triangle6
        // 0,b,0,
        // 0,b,h, //OBH :P
        // l,b,h,
        -ll1/2, -bb1/2, -hh1/2,
        ll1/2, bb1/2, -hh1/2,
        ll1/2, -bb1/2, -hh1/2,
        // //lateralside3
        // //triangle7
        // 0,b,0,
        // 0,b,h,
        // 0,0,h,
        -ll1/2, bb1/2, -hh1/2,
        -ll1/2, -bb1/2, -hh1/2,
        -ll1, bb1, hh1,
        // //triangle8
        // 0,0,h,
        // 0,b,0,
        // 0,0,0,
        -ll1, bb1, hh1,
        -ll1/2,-bb1/2, -hh1/2,
        -ll1, -bb1, hh1,
        // //lateralside4
        // //triangle9
        // 0,0,h,
        // 0,0,0,
        // l,0,b,
        ll1/2, bb1/2, -hh1/2,
        ll1/2, -bb1/2, -hh1/2,
        ll1, bb1, hh1,
        // //triangle10
        // 0,0,0,
        // l,0,b,
        // l,0,0,
        ll1, bb1, hh1,
        ll1/2,-bb1/2, -hh1/2,
        ll1, -bb1, hh1,
        // //downside
        // //triangle11
        // 0,0,0,
        // l,0,0,
        // 0,b,0,
        -ll1/2, -bb1/2, -hh1/2,
        -ll1, -bb1, hh1,
        ll1/2, -bb1/2, -hh1/2,
        // //triangle12
        // l,b,0,
        // l,0,0,
        // 0,b,0
        ll1/2, -bb1/2, -hh1/2,
        -ll1, -bb1, hh1,
        ll1, -bb1, hh1

   };
   const GLfloat vertex_buffer_data1[] = {
     0,0,hh1/2+3,
     0,-1,hh1/2+3,
     0,0,hh1/2+4,
   };
   const GLfloat vertex_buffer_data2[] = {
     0,0,hh1/2,
     0,0,hh1/2+4,
     0,0.1,hh1/2+4,

     0,0.1,hh1/2+4,
     0,0.1,hh1/2,
     0,0,hh1/2

   };
   //this->cannon=Cube(ll1-1.5,bb1-1,hh1,0.6,0.6,3,COLOR_ORANGE);
   //this->cannontop=Cube(ll1-1.5,bb1-1,hh1+1.5,1.1,1.1,1,COLOR_LRED);


    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_YELLOW, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    //cannon.draw(VP);
    //cannontop.draw(VP);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
   // this->rotation += speed;
     this->position.x += speedx;
    this->position.y += speedy;
    // this->position.z +=speedz;
  }
  bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y,0.4,0.4};
    return bbox;
}
