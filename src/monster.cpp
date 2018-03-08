#include "monster.h"
#include "main.h"
float ll2,bb2,hh2;
Monster::Monster(float x, float y, float z ) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedx=(float)rand()/((float)RAND_MAX/0.01);
    // this->speedy=0;
    this->speedy=(float)rand()/((float)RAND_MAX/0.01);
    ll2=4/2;
    bb2=3/2;
    hh2=2/2;
    const GLfloat vertex_buffer_data[] = {
      //triangle1
      // 0,0,h,
      // l,0,b,
      // l,b,h,
      -ll2, bb2, -hh2,
      -ll2, bb2, hh2,
      ll2, bb2, -hh2,
      // //triangle2
      // 0,0,h,
      // l,b,h,
      // 0,b,h,
      ll2, bb2, -hh2,
      -ll2, bb2, hh2,
      ll2, bb2, hh2,
      // //lateralside1
      // //triangle3
      // l,0,b,
      // l,0,0,
      // l,b,h,
      -ll2, bb2, hh2,
      ll2, bb2, hh2,
      -ll2, -bb2, hh2,
      // //triangle4
      // l,b,h,
      // l,0,0,
      // l,b,0,
      -ll2, -bb2, hh2,
      ll2, bb2, hh2,
      ll2, -bb2, hh2,
      // //lateralside2
      // //triangle5
      // l,b,h,
      // l,b,0,
      // 0,b,0,
      -ll2, bb2, -hh2,
      ll2, bb2, -hh2,
      -ll2, -bb2, -hh2,

      // //triangle6
      // 0,b,0,
      // 0,b,h, //OBH :P
      // l,b,h,
      -ll2, -bb2, -hh2,
      ll2, bb2, -hh2,
      ll2, -bb2, -hh2,
      // //lateralside3
      // //triangle7
      // 0,b,0,
      // 0,b,h,
      // 0,0,h,
      -ll2, bb2, -hh2,
      -ll2, -bb2, -hh2,
      -ll2, bb2, hh2,
      // //triangle8
      // 0,0,h,
      // 0,b,0,
      // 0,0,0,
      -ll2, bb2, hh2,
      -ll2,-bb2, -hh2,
      -ll2, -bb2, hh2,
      // //lateralside4
      // //triangle9
      // 0,0,h,
      // 0,0,0,
      // l,0,b,
      ll2, bb2, -hh2,
      ll2, -bb2, -hh2,
      ll2, bb2, hh2,
      // //triangle10
      // 0,0,0,
      // l,0,b,
      // l,0,0,
      ll2, bb2, hh2,
      ll2,-bb2, -hh2,
      ll2, -bb2, hh2,
      // //downside
      // //triangle11
      // 0,0,0,
      // l,0,0,
      // 0,b,0,
      -ll2, -bb2, -hh2,
      -ll2, -bb2, hh2,
      ll2, -bb2, -hh2,
      // //triangle12
      // l,b,0,
      // l,0,0,
      // 0,b,0
      ll2, -bb2, -hh2,
      -ll2, -bb2, hh2,
      ll2, -bb2, hh2


   };
   const GLfloat vertex_buffer_data1[] = {
     ll2/2,bb2/2,hh2,
     ll2/2,bb2/2,hh2+1,
     ll2/2+1,bb2/2,hh2,

     -ll2/2,bb2/2,hh2,
     -ll2/2,bb2/2,hh2+1,
     -ll2/2-1,bb2/2,hh2,

     ll2/2,-bb2/2,hh2,
     ll2/2,-bb2/2,hh2+1,
     ll2/2+1,-bb2/2,hh2,

     -ll2/2,-bb2/2,hh2,
     -ll2/2,-bb2/2,hh2+1,
     -ll2/2-1,-bb2/2,hh2,

   };
   const GLfloat vertex_buffer_data2[] = {
     ll2/2,0,hh2,
     -ll2/2,0,hh2,
     0,0,hh2+2
   };


    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_BOAT1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_BOAT2, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Monster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Monster::tick() {
   // this->rotation += speed;
     this->position.x += speedx;
    this->position.y += speedy;
    // this->position.z +=speedz;
  }
  bounding_box_t Monster::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bb2ox = { x, y,0.4,0.4};
    return bb2ox;
}
