#include "Shape.h"

class Play{
private:
    bool paused=0;
    bool stopped=0;
    int angle = 20;
    int camera=-30;
    float cameraX=0;
    float cameraZ=0;
    float radius=25;
public:
    Shape shape;
    void init(void);
    void keyboard(int key, int x, int y);
    void normal_Keyboard(unsigned char key, int x, int y);
    bool isActive();
    void stop();
    void displayString(char* string, float x, float y, float z); //to display timer
};

void Play::init()
{
    cameraX= sinf(camera*PI/180.0)*radius;
    cameraZ= cosf(camera*PI/180.0)*radius;
    gluLookAt(cameraX, 4.0, cameraZ, 0, -0.0, 0, 0, 1.0, 0.0);
    shape.robot.displayArm();
    shape.drawGrid();
    shape.drawShape();
    if(!stopped&&shape.spacebar==1)
    {
        if(shape.isGrey()&&shape.spacebar)
        {
            stop();
            paused=1;
        }
        if(paused==0)
        {
            shape.move_down();
        }
        if(shape.screen_fill()==true)
            exit(EXIT_SUCCESS);
    }
    if(stopped)
    {
        displayString("Game Stopped", -4.5, 3.0, 2);
        displayString("Press Restart", -4.1, 0.0, 2);
    }
}



void Play::keyboard(int key, int x, int y)
{
    int state = glutGetModifiers();
    switch(key)
    {
        case GLUT_KEY_UP:
            if(!paused)
                shape.rotate();
            break;
        case GLUT_KEY_DOWN:
            if(!paused)
                shape.move_down();
            break;
        case GLUT_KEY_LEFT:
            if(state==GLUT_ACTIVE_CTRL) 
            {
                camera-=angle;
                if((camera/90)%2 !=0)
                    camera-=angle;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(state==GLUT_ACTIVE_CTRL) 
            {
                camera+=angle;
                if((camera/90)%2 !=0)
                camera+=angle;
            }
            break;
            
    }
}

void Play::normal_Keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 32:
            if(shape.spacebar == 0)
                shape.spacebar = 1;
            else
                shape.spacebar = 0;
            break;
        case 'p': case 'P':
            if(!stopped)
            {
                if(paused==0)
                    paused = 1;
                else
                    paused = 0;
            }
            break;
        case 'q': case 'Q':
            exit(EXIT_SUCCESS);
            break;
        case 'r': case 'R':
            shape.restart();
            stopped=0;
            shape.robot.init();
            paused=0;
            camera=-30;
            break;
        case 'w': case 'W':
        // Increase upper_arm angle
            if(!stopped && !paused)
            {
                shape.robot.Angle[1] += 5.0;
                if ( shape.robot.Angle[1] > 360.0 )
                    shape.robot.Angle[1] -= 360.0;
            }
            break;
        case 'a': case 'A':
            // Increase lower_arm angle
            if(!stopped && !paused)
            {
                shape.robot.Angle[0] += 5.0;
                if ( shape.robot.Angle[0] > 90.0 )
                    shape.robot.Angle[0] -= 5.0;
            }
            break;
        case 's': case 'S':
            // Decrease the upper_arm angle
            if(!stopped && !paused)
            {
                shape.robot.Angle[1] -= 5.0;
                if ( shape.robot.Angle[1]< 0.0 )
                    shape.robot.Angle[1] += 360.0;
            }
            break;
        case 'd': case 'D':
            // Decrease the lower_arm angle
            if(!stopped && !paused)
            {
                shape.robot.Angle[0] -= 5.0;
                if ( shape.robot.Angle[0]< -90.0 )
                    shape.robot.Angle[0] += 5.0;
            }
            break;
    }
}

bool Play::isActive()
{
    return (!paused);
}

void Play::stop()
{
    stopped=true;
    return;
}

void Play::displayString(char* string, float x, float y, float z)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    char *c;
        glPushMatrix();
            glLineWidth(4.0);
            glTranslatef(x,y,z);
            glScalef(0.01f,0.015f,z);
            for (c=string; *c != '\0'; c++)
            {
                  glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
            }
            glLineWidth(1.0);
        glPopMatrix();
}
