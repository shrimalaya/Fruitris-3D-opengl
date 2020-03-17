#include<GL/glut.h>
#include "math.h"

using namespace std;

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define GL_SILENCE_DEPRECATION

#define PI 3.14159265

class Robot {
public:
    float Angle[2] = {0.0}; //0=lower_arm, 1=upper_arm
//    Robot();
    void init();
    void drawArm(int width, int height, float depth, float zFar);
    void lowerArm();
    void base();
    void upperArm();
    void displayArm();
    float getX();
    float getY();
    const float BASE_HEIGHT = 1.0;
    const float BASE_WIDTH = 5.0;
    const float LOWER_ARM_HEIGHT = 15.0;
    const float LOWER_ARM_WIDTH  = 1.0;
    const float UPPER_ARM_HEIGHT = 10.0;
    const float UPPER_ARM_WIDTH  = 1.0;
private:
    float x_length=0;
    float y_length=0;
};

//Robot::Robot()
//{
//    base();
//    lowerArm();
//    upperArm();
//}

//--------------------------------------------------------------------
void Robot::init()
{
    Angle[0] = 0;
    Angle[1] = 0;
    base();
    lowerArm();
    upperArm();
}
//--------------------------------------------------------------------

void Robot::drawArm(int x, int y, float z, float zf) //(x,y) = (width, height)
{
    //Draw a solid square for any given origin
    glBegin(GL_QUADS);

        glVertex3f(0.0,0.0,z);  //Front
        glVertex3f(x,0.0,z);
        glVertex3f(x,y,z);
        glVertex3f(0.0,y,z);

        glVertex3f(0,0.0,zf); //Back
        glVertex3f(0,y,zf);
        glVertex3f(x,y,zf);
        glVertex3f(x,0,zf);

        glVertex3f(0,y,z); //Top
        glVertex3f(x,y,z);
        glVertex3f(x,y,zf);
        glVertex3f(0,y,zf);

        glVertex3f(0,0,z);  //Bottom
        glVertex3f(0,0,zf);
        glVertex3f(x,0,zf);
        glVertex3f(x,0,z);

        glVertex3f(0,0,z);  //Left
        glVertex3f(0,y,z);
        glVertex3f(0,y,zf);
        glVertex3f(0,0,zf);

        glVertex3f(x,0,z);   //Right
        glVertex3f(x,0,zf);
        glVertex3f(x,y,zf);
        glVertex3f(x,y,z);

    glEnd();
    
    glColor3f(0, 0, 0);
    //glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);

        glVertex3f(0.0,0.0,z);  //Front
        glVertex3f(x,0.0,z);
        glVertex3f(x,y,z);
        glVertex3f(0.0,y,z);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,0.0,zf); //Back
        glVertex3f(0,y,zf);
        glVertex3f(x,y,zf);
        glVertex3f(x,0,zf);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,y,z); //Top
        glVertex3f(x,y,z);
        glVertex3f(x,y,zf);
        glVertex3f(0,y,zf);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,0,z);  //Bottom
        glVertex3f(0,0,zf);
        glVertex3f(x,0,zf);
        glVertex3f(x,0,z);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(0,0,z);  //Left
        glVertex3f(0,y,z);
        glVertex3f(0,y,zf);
        glVertex3f(0,0,zf);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(x,0,z);   //Right
        glVertex3f(x,0,zf);
        glVertex3f(x,y,zf);
        glVertex3f(x,y,z);

    glEnd();
    glFlush();
    
    return;
}

//-------------------------------------------------------------
void Robot::base()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-7.0-BASE_WIDTH, -10.0, 0.0 );
        drawArm(BASE_WIDTH, BASE_HEIGHT, 2, -2);
    glPopMatrix();
}
//-------------------------------------------------------------
void Robot::lowerArm()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-5.0-BASE_WIDTH, -10+BASE_HEIGHT, 0.0);
        glRotatef(Angle[0], 0.0, 0.0, 1.0);
        drawArm(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, 0.5, -0.5);
    glPopMatrix();
}
//-------------------------------------------------------------
void Robot::upperArm()
{
    x_length=-5.0-BASE_WIDTH-(LOWER_ARM_HEIGHT*sinf((Angle[0]*PI)/180.0));
    //cout<<endl<<getX()<<endl;
    y_length=-10+(LOWER_ARM_HEIGHT*cosf((Angle[0]*PI)/180.0))+BASE_HEIGHT;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glColor3f(0.4, 0.4, 0.4);
        glTranslatef(x_length,y_length,0.0);
        glRotatef(-90+Angle[1], 0.0, 0.0, 1.0);
        drawArm(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, 0.5, -0.5);
    glPopMatrix();
}
//-------------------------------------------------------------
void Robot::displayArm()
{
    base();
    lowerArm();
    upperArm();
}
//-------------------------------------------------------------
float Robot::getX()
{
    return this->x_length;
}
//-------------------------------------------------------------
float Robot::getY()
{
    return this->y_length;
}
