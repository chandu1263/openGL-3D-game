#include "main.h"
#include "boss.h"
#include "timer.h"
#include "pyramid.h"
#include "cube.h"
#include "water.h"
#include "boat.h"
#include "cannon.h"
//#include "boat.cpp"
////#include "monster.cpp"
#include "monster.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int lives;
int health;
int score;
int timer,times;
int win=0;
/**************************
* Customizable functions *
**************************/
//Pyramid pyramid;
int fired,flag,flag1,flag2,boost;
float alpha,beeta;
Water water;
Cube bullet;
Cube thrower;
Pyramid rock1;
Pyramid rock2;
Pyramid rock3;
Pyramid rock4;
Pyramid rock5;
Pyramid rock6;
Cannon cannon;
Pyramid rocks[160];
int randl[160]={0},randb[160]={0},randx[160]={0},randy[160]={0};
Boat boat;
Boss boss;
Monster monster[10];
int i;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float pixel=0;
int monster_count;
float sun=0,moon=0;
void lockandload()
{
  bullet.position.x=boat.position.x;
  bullet.position.y=boat.position.y;
  fired=0;
  flag=1;
}
bool detect_collision_invincible(bounding_box_t rock, bounding_box_t boat) {
    return ((abs(rock.x-boat.x)<=2.5)&&(abs(rock.y-boat.y)<=3.5));
}
bool detect_collision_vincible(bounding_box_t rock,bounding_box_t boat,int kk,int kk1)
{
  return ((abs(rock.x-boat.x)<=(1.5+kk1))&&(abs(rock.y-boat.y)<=(2.5+kk)));
}
bool detect_collision_monster(bounding_box_t monster, bounding_box_t boat)
{
  return ((abs(monster.x-boat.x)<=4.5)&&(abs(monster.y-boat.y)<=3));
}
bool detect_collision_boss(bounding_box_t boss,bounding_box_t boat)
{
  return ((abs(boss.x-boat.x)< 5.5+2*monster_count)&&(abs(boss.y-boat.y)<3+2*monster_count));
}
bool detect_collision_hitboss(bounding_box_t boss, bounding_box_t boat)
{
  return ((abs(boss.x-boat.x)<= 5.5)&&(abs(boss.y-boat.y)<=3));
}
bool detect_collision_bomb(bounding_box_t rock,bounding_box_t bullet,float kk,float kk1)
{
  return ((abs(bullet.x-rock.x)<=(0.1+kk1))&&(abs(bullet.y-rock.y)<=(0.1+kk)));
}
bool detect_killing_monster(bounding_box_t monster,bounding_box_t bullet)
{
  return ((abs(bullet.x-monster.x)<=(2))&&(abs(bullet.y-monster.y)<=(2)));
}
bool detect_boss_bullet(bounding_box_t boss,bounding_box_t bullet)
{
  return ((abs(boss.x-bullet.x)<=(4))&&(abs(boss.y-bullet.y)<=(4)));
}
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //
    //glm::vec3 eye,target,up;

      // boat following view
      if(boat.view)
      {
        glm::vec3 eye ( boat.position.x-3,boat.position.y,15);
      // Target - Where is the camera looking at.  Don't change unless you are sure!!
      glm::vec3 target (boat.position.x,boat.position.y,-1);
      // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
      glm::vec3 up (1, 0,0);
      Matrices.view = glm::lookAt( eye, target, up );

    }
    // view from some random point
    if(boat.view==2)
    {
      glm::vec3 eye ( pixel+20*cos(camera_rotation_angle*M_PI/180.0f),  pixel+20*sin(camera_rotation_angle*M_PI/180.0f),0 );
      // Target - Where is the camera looking at.  Don't change unless you are sure!!
      glm::vec3 target (0, 0, 0);
      // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
      glm::vec3 up (0, 0, 1);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    // frpm helicopter
    if(boat.view==3)
    {
      glm::vec3 eye ( pixel+20*cos(camera_rotation_angle*M_PI/180.0f),  pixel+20*sin(camera_rotation_angle*M_PI/180.0f),70);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (boat.position.x,boat.position.y,-1);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1,0);
    Matrices.view = glm::lookAt( eye, target, up );
    }
    //helicopter moving along with boat
    if(boat.view==4)
    {
      glm::vec3 eye (boat.position.x-30,boat.position.y-30,70);
      glm::vec3 target (boat.position.x,boat.position.y,-1);
      // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
      glm::vec3 up (0, 1,0);
      Matrices.view = glm::lookAt( eye, target, up );
    }
    //boat view
    if(boat.view==5)
    {
      glm::vec3 eye ( boat.position.x,boat.position.y,0.5 );
      // Target - Where is the camera looking at.  Don't change unless you are sure!!
      glm::vec3 target (boat.position.x,boat.position.y+5,2);
      // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
      glm::vec3 up (0, 0, 1);
      Matrices.view = glm::lookAt( eye, target, up );
    }
        // Compute Camera matrix (view)
     // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!


    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  // MVP = Projection * View * Model
    for(i=0;i<150;i++)
    {
      if(rocks[i].appear)
      rocks[i].draw(VP);
    }
    // Scene render
    water.draw(VP);
    //pyramid.draw(VP);
    if(rock1.appear)
    rock1.draw(VP);
    if(rock2.appear)
    rock2.draw(VP);
    if(rock3.appear)
    rock3.draw(VP);
    if(rock4.appear)
    rock4.draw(VP);
    if(rock5.appear)
    rock5.draw(VP);
    if(rock6.appear)
    rock6.draw(VP);
    boat.draw(VP);
    for(i=0;i<10;i++)
    {if(monster[i].appear)
    monster[i].draw(VP);}
    if(monster_count<=5)
    boss.draw(VP);
    cannon.draw(VP);
    if(fired)
    bullet.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left) {
      camera_rotation_angle +=1;
    }
    if(right){
      camera_rotation_angle +=1;
    }
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if(up)
    {
      pixel +=0.1;
    }
    if(down)
    {
      pixel -=0.1;
    }int bulletfiring = glfwGetKey(window,GLFW_KEY_SPACE);
    int cannonmoveclock = glfwGetKey(window, GLFW_KEY_J);
    int cannonmoveanticlock = glfwGetKey(window, GLFW_KEY_L);
    int boatleft = glfwGetKey(window, GLFW_KEY_A);
    int boatup = glfwGetKey(window, GLFW_KEY_W);
    int boatdown = glfwGetKey(window, GLFW_KEY_S);
    int boatright = glfwGetKey(window, GLFW_KEY_D);
    int booster = glfwGetKey(window, GLFW_KEY_P);
    if(booster)
    {
      if(boost>0)
      {
        flag2=2;
        boost--;
        timer=0;
      }
    }
    if(boatup)
    {
      boat.position.y += 0.1*flag2;
      cannon.cannon1.position.y += 0.1*flag2;
      cannon.cannontop.position.y += 0.1*flag2;
      cannon.gun.position.y += 0.1*flag2;
      if(flag&&!fired)
      bullet.position.y += 0.1*flag2;
    }
    if(boatdown)
    {
      boat.position.y -= 0.1*flag2;
      cannon.cannon1.position.y -= 0.1*flag2;
      cannon.cannontop.position.y -= 0.1*flag2;
      cannon.gun.position.y -= 0.1*flag2;
      if(flag&&!fired)
      bullet.position.y -= 0.1*flag2;
    }
    if(boatright)
    {
      boat.position.x += 0.1*flag2;
      cannon.cannon1.position.x += 0.1*flag2;
      cannon.cannontop.position.x += 0.1*flag2;
      cannon.gun.position.x += 0.1*flag2;
      if(flag&&!fired)
      bullet.position.x += 0.1*flag2;
    }
    if(boatleft)
    {
      boat.position.x -= 0.1*flag2  ;
      cannon.cannon1.position.x -= 0.1*flag2;
      cannon.cannontop.position.x -= 0.1*flag2;
      cannon.gun.position.x -= 0.1*flag2;
      if(flag&&!fired)
      bullet.position.x -= 0.1*flag2;
    }
    int boatview2 = glfwGetKey(window, GLFW_KEY_C);
    if(boatview2)
    {
      boat.view=2;
    }
    int boatview1 = glfwGetKey(window, GLFW_KEY_V);
    if(boatview1)
    {
      boat.view=1;
    }
    int boatview3 = glfwGetKey(window, GLFW_KEY_B);
    if(boatview3)
    {
      boat.view=3;
    }
    int boatview4 = glfwGetKey(window, GLFW_KEY_N);
    if(boatview4)
    {
      boat.view=4;
    }
    int boatview5 = glfwGetKey(window, GLFW_KEY_M);
    if(boatview5)
    {
      boat.view=5;
    }
    if(cannonmoveclock)
    {
      cannon.cannon1.rotation-=0.5;
      cannon.cannontop.rotation-=0.5;
      cannon.gun.rotation-=0.5;
    }
    if(cannonmoveanticlock)
    {
      cannon.cannon1.rotation+=0.5;
      cannon.cannontop.rotation+=0.5;
      cannon.gun.rotation+=0.5;
    }
    if(bulletfiring)
    {
      fired=1;
    }

    if(detect_collision_invincible(rock2.bounding_box(),boat.bounding_box()))
    {
      if(rock2.appear)
      {
      rock2.appear=0;
      score +=5;boost++;

      }
    }
    if(detect_collision_invincible(rock3.bounding_box(),boat.bounding_box()))
    {
      if(rock3.appear){
      rock3.appear=0;
      score +=5;boost++;}
    }
    if(detect_collision_invincible(rock4.bounding_box(),boat.bounding_box()))
    {
      if(rock4.appear){
      rock4.appear=0;
      score +=5;boost++;}
    }
    if(detect_collision_invincible(rock5.bounding_box(),boat.bounding_box()))
    {
      if(rock5.appear){
      rock5.appear=0;
      score +=5;boost++;}
    }
    if(detect_collision_invincible(rock1.bounding_box(),boat.bounding_box()))
    {
      if(rock1.appear){
      rock1.appear=0;
      score +=5;boost++;}
    }
    if(detect_collision_invincible(rock6.bounding_box(),boat.bounding_box()))
    {
      if(rock6.appear){
      rock6.appear=0;
      score +=5;boost++;}
    }
    if(detect_collision_boss(boss.bounding_box(),boat.bounding_box()))
    {
      printf("danger\n" );
      health -= 10;
    }
    if(detect_boss_bullet(boss.bounding_box(),boat.bounding_box()))
    {
      if(monster_count<=5)
      {
        win=1;
        printf("you won the game!!!\n");

    }
    }
    if(detect_collision_hitboss(boss.bounding_box(),boat.bounding_box()))
    {
      printf("gameover!!\n");
      lives=0;

    }
    for(i=0;i<10;i++)
    {
        if(detect_collision_monster(monster[i].bounding_box(),boat.bounding_box()))
        {
          if(monster[i].appear){
          health -=50;
          monster[i].appear=0;
        monster_count--;}
        }
        if(detect_killing_monster(monster[i].bounding_box(),bullet.bounding_box()))
        {
          if(monster[i].appear)
          {
            score+=25;
            monster[i].appear=0;
          monster_count--;
          flag=0;
          }
        }
    }
    int yy;
    for(i=0;i<150;i++)
    {
      if(i%2)
        yy=-1;
      else yy=1;
      if(detect_collision_vincible(rocks[i].bounding_box(),boat.bounding_box(),randl[i],randb[i]))
      {
        if(rocks[i].appear){
        rocks[i].appear=0;
        //boat.position.x += yy*(float)rand()/((float)RAND_MAX/0.3);
        //boat.position.y += yy*(float)rand()/((float)RAND_MAX/0.3);
        {
          //system(" canberra-gtk-play -f  ../sounds/bomb.wav --volume=\"5\" &");

          health -=10;
        printf("health reduced!!!\n" );}
        }
        //printf("died\n" );
      }
      if(detect_collision_bomb(bullet.bounding_box(),rocks[i].bounding_box(),randl[i],randb[i]))
      {
        if(rocks[i].appear)
        {
          score+=10;
          rocks[i].appear=0;
          flag=0;
        }
      }
    }
    sun=boat.position.x;
    moon=boat.position.y;
}

void tick_elements() {
    if(timer==0)
  {
    times++;
  }
  if(times>=300)
  {
    flag2=1;
    timer=1;
  }
  if(flag&&fired)
  {
      alpha=cannon.cannon1.rotation;
      bullet.position.x+=0.6*sin(alpha*M_PI/180.0f);
      bullet.position.y+=0.6*cos(alpha*M_PI/180.0f);
  }
  if(flag==0)
  lockandload();
  if((abs(boat.position.x-bullet.position.x)>=20)||(abs(boat.position.y-bullet.position.y)>=20))
  {
    lockandload();
  }




for(i=0;i<10;i++)
{
  if(monster[i].appear)
monster[i].tick();
}
boat.tick();
for(i=0;i<150;i++)
{
  if(rocks[i].appear)
    rocks[i].tick();
}
if(monster_count<=5)
boss.tick();
float slope=(boat.position.y-boss.position.y)/(boat.position.x-boss.position.x);
if(monster_count<=5)
{
boss.position.x -= 0.1;
boss.position.y = boss.position.y - (0.1/slope);
}
rock1.tick1();
rock2.tick1();
rock3.tick1();
rock4.tick1();
rock5.tick1();
rock6.tick1();
}
int randomx,randomy,randoml,randomb,randomh;
int mulx,muly;
color_t colour;

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    timer=1;
    times=0;
    fired=0;
    //pyramid = Pyramid(0,0,-1,1,1,2,COLOR_BROWN);
    water   = Water(0,0,-2,COLOR_BLUE);
    rock1   = Pyramid(50,10,-1,3,2,2,COLOR_BLACK);
    rock1.appear=1;
    rock2   = Pyramid(65,45,-1,1,1,1,COLOR_BLACK);
    rock2.appear=1;
    rock3   = Pyramid(-35,110,-1,1,1,1,COLOR_BLACK);
    rock3.appear=1;
    rock4   = Pyramid(115,-100,-1,1,1,1,COLOR_BLACK);
    rock4.appear=1;
    rock5   = Pyramid(85,85,-1,1,1,1,COLOR_BLACK);
    rock5.appear=1;
    rock6   = Pyramid(-95,-40,-1,1,1,1,COLOR_BLACK);
    rock6.appear=1;
    boat = Boat(0,0,-1,5,3,2,COLOR_BROWN);
    boat.view=2;
    boss = Boss(90,90,-1);
    cannon=Cannon(0,0,0);
    bullet=Cube(0,0,1,0.3,0.3,0.3,COLOR_BLACK);
    //thrower=Cube(boat.position.x,boat.position.y-1,5,,,,COLOR_ORANGE);
    for(i=0;i<10;i++)
    {
      randomx=(rand()%10000)/100;
      randomy=(rand()%10000)/100;
      monster[i] = Monster(randomx,randomy,-1);
      monster[i].appear=1;
    }
    for(i=0;i<150;i++)
    {

      if(i%3==0)
      {
        randoml=0.75;
        randomb=0.75;
        mulx=1;
        muly=-1;
        randl[i]=randoml;
        randb[i]=randomb;
      }
      if(i%3==1)
      {
        randoml=1.25;
        randomb=1.25;
        mulx=1;
        muly=1;
        randl[i]=randoml;
        randb[i]=randomb;
      }
      if(i%3==2)
      {
        randoml=2;
        randomb=2;
        mulx=-1;
        muly=-1;
        randl[i]=randoml;
        randb[i]=randomb;
      }
      if(i%4==0)
      {
        randomh=1;
        colour = COLOR_ROCK1;
        mulx=-1;
        muly=1;
        randl[i]=randoml;
        randb[i]=randomb;
      }
      if(i%4==1)
      {
        randomh=2;
        colour = COLOR_ROCK2;
      }
      if(i%4==2)
      {
        randomh=1;
        colour = COLOR_ROCK3;
      }
      if(i%4==3)
      {
        randomh=2;
        colour = COLOR_ROCK4;
      }

      randomx=(rand()%10000)/100;
      randomy=(rand()%10000)/100;

       randx[i]=randomx*mulx;
       randy[i]=randomy*muly;
      rocks[i]= Pyramid(mulx*randomx,muly*randomy,-1,randoml,randomb,randomh,colour);
      rocks[i].appear=1;
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand((0));
    int width  = 600;
    int height = 600;
    score=0;
    health=100;
    lives=10;
    boost=0;
    flag2=1;
    flag=1;
    monster_count=10;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
          if(win)
          {
            printf("congrats\n" );
            break;
          }
            if(lives<=0)
            {
              printf("Game over!!\n" );
              system("pkill canberra-gtk-pl");
              break;
            }
            if(health<=0)
            {
              printf("life gone!!!!\n" );
              lives--;
              health=100;
            }
            //////////////////////////

          string Result;
          stringstream convert;
          //cout << "nonedit score:" << score << endl;
          convert << score;
          Result = convert.str();

          const char *one = "Score ";
          const char *two = Result.c_str();
          const char *three = "   Lives ";
          string Result1;
          stringstream convert1;
          convert1 << lives;
          Result1 = convert1.str();
          const char *four = Result1.c_str();
          const char *five = "  Health ";
          string Result2;
          stringstream convert2;
          convert2<<health;
          Result2 = convert2.str();
          const char * six = Result2.c_str();

          string Result3;
          stringstream convert3;
          convert3 << monster_count;
          Result3 = convert3.str();
          const char * seven = "  MONSTERS ";
          const char * eight =  Result3.c_str();

          string Result4;
          stringstream convert4;
          convert4 << boost;
          Result4 = convert4.str();
          const char * nine = "  Boost ";
          const char * ten =  Result4.c_str();

          string total( string(one) + two + string(three) + four +string(five) + six + string(seven)+eight + string(nine)+ten);
          glfwSetWindowTitle(window, total.c_str());


             ////////////////////////////////

            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}



void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::infinitePerspective(45.0f,1.0f,0.1f);
}
