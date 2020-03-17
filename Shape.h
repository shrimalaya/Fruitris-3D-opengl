#ifndef Shape_h
#define Shape_h

#include <string>
#include "time.h"
#include <cstdlib>
#include <cstring>
#include "Robot.h"

int frameRate = 3;
int countTime=4*frameRate-1;

class Shape{
private:
    int  x_position;
    int  y_position=8;
    int  angle;
    
    string letter;
    int color[5] = {0, 0, 0, 0, 0};                 //1= Purple, 2= Red, 3= Yellow, 4= Green, 5= Orange
    int boxes[4][4];
    int grey[4][4];
    int grid[20][10];
    
public:
    bool spacebar=0;
    Robot robot;
    Shape();
    void init();
    
    string randLetter(void);
    void randTile(void);
    void pos();
    void obj_angle();
    
    bool isGrey();
    void drawCube(int x, int y, int color);
    void drawShape(void);
    void drawGrid(void);
    
    void rotateI();
    void rotate();
    void move_down();
    void move_left();
    void move_right();

    bool collision_down();                            //Check for collision with bottom
    bool collision_left();                            //Check for collision with left
    bool collision_right();                           //Check for collision with right
    bool turnGrey();
    
    void update();                                    //Update the current grid
    void restart();                                   //Restart when 'r' is pressed
    bool screen_fill();
};

Shape::Shape()
{
    srand(time(0));
    randTile();             //Random color
    letter=randLetter();    //Random shape for the tetris
    pos();                //Initialize random x and y positions
    obj_angle();            //Random angle
    //Initialize grid to be empty
    for(int i=0; i<10; i++)
        for(int j=0; j<20; j++)
            grid[j][i] = 0;
}

void Shape::init()
{
    spacebar=0;
    countTime=4*frameRate-1;
    pos();                //Initialize random x position
    randTile();             //Random color
    letter=randLetter();    //Random shape for the tetris
    obj_angle();            //Random angle
    return;
}

string Shape::randLetter(void)
{
    int temp = rand()%6 +1;
    if(temp == 1) {
        int boxes_I[4][4] = {{0, 0, color[3], 0},{0, 0, color[2], 0},{0, 0, color[1], 0},{0, 0, color[0], 0}};
        memcpy(boxes, boxes_I, 4*4*sizeof(int));
        return "I";     //I
    }
    else if(temp == 2) {
        int boxes_S[4][4] = {{0, 0, 0, 0},{0, 0, color[2], color[3]},{0, color[0], color[1], 0},{0, 0, 0, 0}};
        memcpy(boxes, boxes_S, 4*4*sizeof(int));
        return "S";     //S
    }
    else if(temp == 3) {
        int boxes_L[4][4] = {{0, 0, color[3], 0},{0, 0, color[2], 0},{0, 0, color[1], color[0]},{0, 0, 0, 0}};
        memcpy(boxes, boxes_L, 4*4*sizeof(int));
        return "L";     //L
    }
    else if(temp==4){
        int boxes_T[4][4] = {{0, 0, 0, 0},{0, color[0], color[2], color[3]},{0, 0, color[1], 0},{0, 0, 0, 0}};
        memcpy(boxes, boxes_T, 4*4*sizeof(int));
        return "T";     //T
    }
    else if(temp == 5) {
        int boxes_J[4][4] = {{0, 0, color[3], 0},{0, 0, color[2], 0},{0, color[0], color[1], 0},{0, 0, 0, 0}};
        memcpy(boxes, boxes_J, 4*4*sizeof(int));
        return "J";     //Inverted L
    }
    else{
        int boxes_Z[4][4] = {{0, 0, 0, 0},{0, color[3], color[2], 0},{0, 0, color[1], color[0]},{0, 0, 0, 0}};
        memcpy(boxes, boxes_Z, 4*4*sizeof(int));
        return "Z";     //Inverted S
    }
}

void Shape::randTile(void)
{
    for(int i=0; i<4; i++)
    {
        int temp = rand()%5+1; //1 = Purple, 2 = Red, 3 = Yellow, 4 = Green, 5 = Orange
        color[i] = temp;        //color data for the grid
    }
    return;
}

void Shape::pos()
{
    x_position = round(robot.getX() +
        robot.UPPER_ARM_HEIGHT*cosf((robot.Angle[1]*PI)/180.0))-1.0;
    y_position = round(robot.getY() +
        robot.UPPER_ARM_HEIGHT*sinf((robot.Angle[1]*PI)/180.0))-2.0 ;
    if((letter=="I"||letter=="L") && angle==270)
    {
        y_position+=1.0;
        x_position-=1.0;
    }
    
    //cout<<endl<<endl<<x_position<<endl<<endl;
    return;
}

void Shape::obj_angle()
{
    angle = (rand()%5)*90;
    if(letter=="I")
    {
        angle = (rand()%2 + 3)*90;
        if(angle==270)
        {
            int temp[4][4];
            
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    temp[i][j] = boxes[i][j];
            
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    boxes[j-1][3-i] = temp[i][j];
            boxes[3][2]=0;
            return;
        }
        else if (angle==360)
        {
            angle=0;
            return;
        }
    }
    for(int i=0; i<angle/90; i++)
    {
        int temp[4][4];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                temp[i][j] = boxes[i][j];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                boxes[3-j][i+1] = temp[i][j];
    }
    return;
}

bool Shape::isGrey()
{
    if(turnGrey()) {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                if(boxes[i][j]!=0)
                    grey[i][j]=6;
                else
                    grey[i][j]=0;
        return true;
    }
    return false;
}

void Shape::drawCube(int x, int y, int color)
{
    if(color==1)                                        //Purple
        glColor3f(145.0/255, 30.0/255, 180.0/255);
    else if(color==2)                                   //Red
        glColor3f(230.0/255, 25.0/255, 75.0/255);
    else if(color == 3)                                 //Yellow
        glColor3f(1.0,1.0, 25.0/255);
    else if(color == 4)                                 //Green
        glColor3f(60.0/255, 180.0/255, 75.0/255);
    else if(color== 5)                                             //Orange
        glColor3f(245.0/255, 130.0/255, 49.0/255);
    else if(color==6) //grey
        glColor3f(0.5, 0.5, 0.5);
    //Draw a solid square for any given origin
    glBegin(GL_QUADS);

        glVertex3f(x,y,1);  //Front
        glVertex3f(x+1,y,1);
        glVertex3f(x+1,y+1,1);
        glVertex3f(x,y+1,1);

        glVertex3f(x,y,0); //Back
        glVertex3f(x,y+1,0);
        glVertex3f(x+1,y+1,0);
        glVertex3f(x+1,y,0);

        glVertex3f(x,y+1,1); //Top
        glVertex3f(x+1,y+1,1);
        glVertex3f(x+1,y+1,0);
        glVertex3f(x,y+1,0);

        glVertex3f(x,y,1);  //Bottom
        glVertex3f(x,y,0);
        glVertex3f(x+1,y,0);
        glVertex3f(x+1,y,1);

        glVertex3f(x,y,1);  //Left
        glVertex3f(x,y+1,1);
        glVertex3f(x,y+1,0);
        glVertex3f(x,y,0);

        glVertex3f(x+1,y,1);   //Right
        glVertex3f(x+1,y,0);
        glVertex3f(x+1,y+1,0);
        glVertex3f(x+1,y+1,1);

    glEnd();

    //Draw an outline for the solid
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINE_LOOP);
        glVertex3f(x+ 0, y+0, 1);
        glVertex3f(x+ 0, y+1, 1);
        glVertex3f(x+1, y+1, 1);
        glVertex3f(x+1, y+0, 1);
    glEnd();
        
    glFlush();
    
    return;
}

void Shape::drawShape(void)
{
    if(spacebar==0)
        pos();
    
    glPushMatrix();
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                if(boxes[i][j]!=0)      //Draw the shape according to the color data in **boxes
                {
                    if(isGrey())
                        drawCube(x_position+((j-2)), y_position - ((i-1)), grey[i][j]);
                    else
                        drawCube(x_position+((j-2)), y_position - ((i-1)), boxes[i][j]);
                }
    
    glPopMatrix();
    return;
}

void Shape::drawGrid(void)
{
    glColor3f(0,0,0.6);
    glBegin(GL_LINES);
    
    //Horizontal
    for(int i=-10; i<=10; i++)
    {
        glColor3f(0,0,0.6);
        glVertex3f(-5, i, 1);
        glVertex3f(5, i, 1);
    }
    glColor3f(0.3, 0, 0);
    glVertex3f(-5, -10, 0);
    glVertex3f(5, -10, 0);
    glVertex3f(-5, 10, 0);
    glVertex3f(5, 10, 0);
    //Vertical
    for(int i=-5; i<=5; i++)
    {
        glColor3f(0, 0, 0.6);
        glVertex3f(i, -10, 1);
        glVertex3f(i, 10, 1);
    }
    glColor3f(0.3, 0, 0);
    glVertex3f(-5, -10, 0);
    glVertex3f(-5, 10, 0);
    glVertex3f(5, -10, 0);
    glVertex3f(5, 10, 0);
    
    glVertex3f(-5, -10, 1);
    glVertex3f(-5, -10, 0);
    
    glVertex3f(5, -10, 0);
    glVertex3f(5, -10, 1);
    
    glVertex3f(-5, 10, 0);
    glVertex3f(-5, 10, 1);
    
    glVertex3f(5, 10, 0);
    glVertex3f(5, 10, 1);
    
    glEnd();
    
    //now update the grid to store the already fallen blocks along with their individual color
    for(int j=0; j<20; j++)
        for(int i=0; i<10; i++)
            if(grid[j][i]!=0)
                drawCube(i-5, (19-j)-10, grid[j][i]);
}

void Shape::rotateI()   //Separate case for I since only two types of rotations possible 0->270 and 270->0
{
    if(angle==0)
    {
        int temp[4][4];
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                temp[i][j] = boxes[i][j];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                boxes[j-1][3-i] = temp[i][j];
        boxes[3][2]=0;
        if(collision_right())
        {
            memcpy(boxes, temp, 4*4*sizeof(int));
            return;
        }
        angle = 270;
        return;
    }
    else if(angle == 270)
    {
        int temp[4][4];
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                temp[i][j] = boxes[i][j];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                boxes[3-j][i+1] = temp[i][j];
        if(collision_down())
        {
            memcpy(boxes, temp, 4*4*sizeof(int));
            return;
        }
        angle = 0;
        return;
    }
}

void Shape::rotate()                                            //rotate 90 degrees counter-clockwise
{
    if(letter=="I")                                             //Check for separate case of I
    {
        rotateI();
        return;
    }
    //Continue standard operation
    if(angle==360 || angle==0)                                  //set angle to 0 if block make one full rotation of 360 degrees
        angle = 0;
    
    int temp[4][4];
    
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            temp[i][j] = boxes[i][j];
    
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            boxes[3-j][i+1] = temp[i][j];
    
    // Check for collision after rotation and
    // go back to original if collision exists
    
    int left = 0;                                              //count the number of times left or right to avoid over-shifting blocks
    if(collision_left()==0)
    {
        left++;
        move_left();
    }
    if(collision_right())
    {
        memcpy(boxes, temp, 4*4*sizeof(int));                   //revert back to the original orientation since collision detected
        if(left>0)
            move_right();
        return;
    }
    if(left>0)
        move_right();                                           //Take use of "counting the moves" to avoid shifting

    int right=0;
    if(collision_right()==0)
    {
        right++;
        move_right();
    }
    if(collision_left())
    {
        memcpy(boxes, temp, 4*4*sizeof(int));                   //revert back to the original orientation since collision detected
        if(right>0)
            move_left();
        return;
    }
    if(right>0)
        move_left();
    angle+=90;
    return;
}
void Shape::move_down()                                         //Move down
{
    if(collision_down()==1) {                                   //Check for collision with either window or another block
        update();                                               //If collision detected, stop and store the current grid data
        init();                                                 //Initialize new Shape
        return;
    }
    y_position-=1;                                             //if no collision, move down by one row (20 units)
    return;
}
void Shape::move_left()                                         //Move left
{
    if(collision_left()==1)                                     //Check for collision with either window or another block
        return;
    
    x_position-=1;                                             //if no collision, move left by one column (20 units)
    return;
}

void Shape::move_right()                                        //Move right
{
    if(collision_right()==1)                                    //Check for collision with either window or another block
        return;
    
    x_position +=1;                                            //Move right by one block if no collision detected
    return;
}

bool Shape::collision_down()                                    //Check for collision from bottom
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position-2+j+5;
                int y1 = 19-y_position+i-10;                    //Check the entire next row from bottom of the Shape
                if(grid[y1][x1]!=0||y1>19)   //Collision from another block or window detected
                    return 1;
            }
    return 0;
}

bool Shape::collision_left()                                    //check for Collision from the left side
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position+5-2+j;
                int y1 = 19-y_position-10+i;
                if(grid[y1-1][x1-1]!=0 || x1-1<0)               //Check the entire column on the left
                    return 1;                                   //Collision from another block or window detected
            }
    return 0;
}

bool Shape::collision_right()                                   //Check for collision from the right side
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position+5-2+j;
                int y1 = 19-y_position-10+i;                    //Check the entire column on the right
                if(grid[y1-1][x1+1]!=0 || x1+1>9)               //Collision from another block or window detected
                    return true;
            }
    return false;
}

bool Shape::turnGrey()
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position+5-2+j;
                int y1 = 19-y_position-10+i;                    //Check the entire column on the right
                if(grid[y1-1][x1]!=0)
                    return true;
                else if(x1+1>10||x1-1<-1||y1>20||y1<1)               //Collision with another block or window detected)
                    return true;
            }
    return false;
}

void Shape::update()                                            //update the integer value of the position og the shape on the grid
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
                grid[19-((y_position+10)+1)+i][(x_position+5)-2+j] = boxes[i][j];
    return;
}

void Shape::restart()
{
    for(int i=0; i<10; i++)
        for(int j=0; j<20; j++)
            grid[j][i]=0;
    init();
    return;
}

bool Shape::screen_fill()                                                   //If the screen if full, quit the game
{
    for(int i=0; i<10; i++)
        if(grid[1][i]!=0)
            return true;
    
    return false;
}


#endif /* Shape_h */
