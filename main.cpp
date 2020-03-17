#include "Play.h"

Play game;
char* countdown = "2.0";    //Initialize countdown value with 2.0 seconds

void init(void) {
    glViewport(0, 0, 400, 800);
    glClearColor(1, 1, 1, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 0.5, 0.1, 100.0);    //Use perspective projection to display in 3D
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST );
    glEnable(GL_LINE_SMOOTH | GL_POLYGON_SMOOTH | GL_BLEND);
}


void keyboard(int key, int x, int y)
{
    game.keyboard(key, x, y);
    return;
}

void normal_Keyboard(unsigned char key, int x, int y)
{
    game.normal_Keyboard(key, x, y);
    return;
}

void countdownTimer()   //Countdown time of 2 seconds
{
    if(game.isActive() && countTime>=0)
    {
        if(countTime/4==2)
            countdown="2.0";
        else if(countTime/4==1)
            countdown="1.0";
        else
            countdown="0.0";

        countTime--;
        if(countTime==0)
            game.shape.spacebar=1;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,-2,0);
    glPushMatrix();     //Push to stop the countdown from being rotated (for better visual)
        glTranslatef(0.3,1.0, -25);
        game.displayString(countdown, -1.4, 11.0, 0);
        game.displayString("Countdown", -3.4, 13, 0);
    glPopMatrix();
    game.init();
    glutSwapBuffers();
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/frameRate, timer, 0);    //frameRate set in "Shape.h"
    countdownTimer();
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(normal_Keyboard);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Double buffer display
    glutInitWindowPosition(50,50);
    glutInitWindowSize(400, 800);
    glutCreateWindow("FRUITris");
    
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}
