 #include "main.h"
 #include "cannon.h"
 #include "cube.h"
// float ll4,bb4,hh4,xr1,xl1,yr1,yl1,xr2,xl2,yr2,yl2;
Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->theeta=0;
//     // this->speedx=0;
//     // this->speedy=0;
//     // this->speedz=0;
//     ll4=l/2;
//     bb4=b/2;
//     hh4=h/2;
//     xr1=l*cos(theeta*M_PI/180.0f)-b*sin(theeta*M_PI/180.0f);
//     xr2=l*cos(theeta*M_PI/180.0f)+b*sin(theeta*M_PI/180.0f);
//     xl1=-l*cos(theeta*M_PI/180.0f)-b*sin(theeta*M_PI/180.0f);
//     xl2=-l*cos(theeta*M_PI/180.0f)+b*sin(theeta*M_PI/180.0f);
//
//     yr1=l*sin(theeta*M_PI/180.0f)+b*cos(theeta*M_PI/180.0f);
//     yr2=l*sin(theeta*M_PI/180.0f)-b*cos(theeta*M_PI/180.0f);
//     yl1=-l*sin(theeta*M_PI/180.0f)+b*cos(theeta*M_PI/180.0f);
//     yl2=-l*sin(theeta*M_PI/180.0f)-b*cos(theeta*M_PI/180.0f);
//     const GLfloat vertex_buffer_data[] = {
//         //topside
//         //triangle1
//         // 0,0,h,
//         // l,0,b,
//         // l,b,h,
//         xl1, yl1, -hh4,
//         xl1, yl1, hh4,
//         xr1, yr1, -hh4,
//         // //triangle2
//         // 0,0,h,
//         // l,b,h,
//         // 0,b,h,
//         xr1, yr1, -hh4,
//         xl1, yl1, hh4,
//         xr1, yr1, hh4,
//         // //lateralside1
//         // //triangle3
//         // l,0,b,
//         // l,0,0,
//         // l,b,h,
//         xl1, yl1, hh4,
//         xr1, yr1, hh4,
//         xl2, yl2, hh4,
//         // //triangle4
//         // l,b,h,
//         // l,0,0,
//         // l,b,0,
//         xl2, yl2, hh4,
//         xr1, yr1, hh4,
//         xr2, yr2, hh4,
//         // //lateralside2
//         // //triangle5
//         // l,b,h,
//         // l,b,0,
//         // 0,b,0,
//         xl1, yl1, -hh4,
//         xr1, yr1, -hh4,
//         xl2, yl2, -hh4,
//
//         // //triangle6
//         // 0,b,0,
//         // 0,b,h, //OBH :P
//         // l,b,h,
//         xl2, yl2, -hh4,
//         xr1, yr1, -hh4,
//         xr2, yr2, -hh4,
//         // //lateralside3
//         // //triangle7
//         // 0,b,0,
//         // 0,b,h,
//         // 0,0,h,
//         xl1, yl1, -hh4,
//         xl2, yl2, -hh4,
//         xl1, yl1, hh4,
//         // //triangle8
//         // 0,0,h,
//         // 0,b,0,
//         // 0,0,0,
//         xl1, yl1, hh4,
//         xl2, yl2 -hh4,
//         xl2, yl2, hh4,
//         // //lateralside4
//         // //triangle9
//         // 0,0,h,
//         // 0,0,0,
//         // l,0,b,
//         xr1, yr1, -hh4,
//         xr2, yr2, -hh4,
//         xr1, yr1, hh4,
//         // //triangle10
//         // 0,0,0,
//         // l,0,b,
//         // l,0,0,
//         xr1, yr1, hh4,
//         xr2, yr2 -hh4,
//         xr2, yr2, hh4,
//         // //downside
//         // //triangle11
//         // 0,0,0,
//         // l,0,0,
//         // 0,b,0,
//         xl2, yl2, -hh4,
//         xl2, yl2, hh4,
//         xr2, yr2, -hh4,
//         // //triangle12
//         // l,b,0,
//         // l,0,0,
//         // 0,b,0
//         xr2, yr2, -hh4,
//         xl2, yl2, hh4,
//         xr2, yr2, hh4
//
//
//    };
//
//     this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
// }
this->cannon1=Cube(x,y-1,z+1,0.6,0.6,3,COLOR_ORANGE);
this->cannontop=Cube(x,y-1,z+3,1.1,1.1,1,COLOR_LRED);
this->gun=Cube(x,y-1,z+3,3,0.6,0.6,COLOR_ORANGE);

}
//
void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object);
    cannon1.draw(VP);
    cannontop.draw(VP);
    gun.draw(VP);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
  // int left  = glfwGetKey(window, GLFW_KEY_LEFT);
  // int right = glfwGetKey(window, GLFW_KEY_RIGHT);
  // if (left) {
  //     theeta += 1;
  // }
  // if(right){
  //   theeta -= 1;
  // }
  // int up  = glfwGetKey(window, GLFW_KEY_UP);
  // int down = glfwGetKey(window, GLFW_KEY_DOWN);
   // this->rotation += speed;
    // this->position.x += speedx;
    // this->position.y += speedy;
    // this->position.z +=speedz;
    this->rotation += 0;
  }
