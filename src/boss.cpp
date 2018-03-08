#include "boss.h"
#include "main.h"
//#include "color.cpp"
const color_t COlOR_BOSS2={193, 21, 156};
const color_t COlOR_BOSS3={60, 224, 15};

float llboss,bbboss,hhboss;
Boss::Boss(float x, float y, float z ) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedx=0;
    // this->speedy=0;
    this->speedy=0;
    llboss=4;
    bbboss=3;
    hhboss=2;
    const GLfloat vertex_buffer_data[] = {
      //triangle1
      // 0,0,h,
      // l,0,b,
      // l,b,h,
      -llboss, bbboss, -hhboss,
      -llboss, bbboss, hhboss,
      llboss, bbboss, -hhboss,
      // //triangle2
      // 0,0,h,
      // l,b,h,
      // 0,b,h,
      llboss, bbboss, -hhboss,
      -llboss, bbboss, hhboss,
      llboss, bbboss, hhboss,
      // //lateralside1
      // //triangle3
      // l,0,b,
      // l,0,0,
      // l,b,h,
      -llboss, bbboss, hhboss,
      llboss, bbboss, hhboss,
      -llboss, -bbboss, hhboss,
      // //triangle4
      // l,b,h,
      // l,0,0,
      // l,b,0,
      -llboss, -bbboss, hhboss,
      llboss, bbboss, hhboss,
      llboss, -bbboss, hhboss,
      // //lateralside2
      // //triangle5
      // l,b,h,
      // l,b,0,
      // 0,b,0,
      -llboss, bbboss, -hhboss,
      llboss, bbboss, -hhboss,
      -llboss, -bbboss, -hhboss,

      // //triangle6
      // 0,b,0,
      // 0,b,h, //OBH :P
      // l,b,h,
      -llboss, -bbboss, -hhboss,
      llboss, bbboss, -hhboss,
      llboss, -bbboss, -hhboss,
      // //lateralside3
      // //triangle7
      // 0,b,0,
      // 0,b,h,
      // 0,0,h,
      -llboss, bbboss, -hhboss,
      -llboss, -bbboss, -hhboss,
      -llboss, bbboss, hhboss,
      // //triangle8
      // 0,0,h,
      // 0,b,0,
      // 0,0,0,
      -llboss, bbboss, hhboss,
      -llboss,-bbboss, -hhboss,
      -llboss, -bbboss, hhboss,
      // //lateralside4
      // //triangle9
      // 0,0,h,
      // 0,0,0,
      // l,0,b,
      llboss, bbboss, -hhboss,
      llboss, -bbboss, -hhboss,
      llboss, bbboss, hhboss,
      // //triangle10
      // 0,0,0,
      // l,0,b,
      // l,0,0,
      llboss, bbboss, hhboss,
      llboss,-bbboss, -hhboss,
      llboss, -bbboss, hhboss,
      // //downside
      // //triangle11
      // 0,0,0,
      // l,0,0,
      // 0,b,0,
      -llboss, -bbboss, -hhboss,
      -llboss, -bbboss, hhboss,
      llboss, -bbboss, -hhboss,
      // //triangle12
      // l,b,0,
      // l,0,0,
      // 0,b,0
      llboss, -bbboss, -hhboss,
      -llboss, -bbboss, hhboss,
      llboss, -bbboss, hhboss


   };
   const GLfloat vertex_buffer_data1[] = {
     llboss/2,bbboss/2,hhboss,
     llboss/2,bbboss/2,hhboss+1,
     llboss/2+1,bbboss/2,hhboss,

     -llboss/2,bbboss/2,hhboss,
     -llboss/2,bbboss/2,hhboss+1,
     -llboss/2-1,bbboss/2,hhboss,

     llboss/2,-bbboss/2,hhboss,
     llboss/2,-bbboss/2,hhboss+1,
     llboss/2+1,-bbboss/2,hhboss,

     -llboss/2,-bbboss/2,hhboss,
     -llboss/2,-bbboss/2,hhboss+1,
     -llboss/2-1,-bbboss/2,hhboss,

   };
   const GLfloat vertex_buffer_data2[] = {
     llboss/2,0,hhboss,
     -llboss/2,0,hhboss,
     0,0,hhboss+2
   };


    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BOSS1, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_BLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_LRED, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
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

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {
   // this->rotation += speed;
     this->position.x += speedx;
    this->position.y += speedy;
    // this->position.z +=speedz;
  }
  bounding_box_t Boss::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbbossox = { x, y,0.4,0.4};
    return bbbossox;
}
