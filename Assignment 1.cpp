//Atiq Israk Niloy (2016100000039)
#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>
#include <windows.h>
#include <glut.h>

using namespace std;

#define eps 0.00001
#define WINDOW_WIDTH 500.0
#define WINDOW_HEIGHT 500.0
#define pi (2*acos(0.0))

#define MAX_VAL 9999999
#define MIN_VAL -9999999

class Point
{
public:
	double x,y,z;

	Point(){
	}
	Point(double a, double b, double c){
        x = a;
        y = b;
        z = c;
	}
	~Point(){}

	double dot(Point v){
        return x*v.x + y*v.y + z*v.z;
	}

	Point operator+(Point pt) {
        return Point(x + pt.x, y + pt.y, z + pt.z);
    }

    Point operator-(Point pt) {
        return Point(x - pt.x, y - pt.y, z - pt.z);
    }

    Point operator*(double v) {

        return Point(x*v, y*v, z*v);
    }

    Point operator*(Point v){
        return Point(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
    }

    Point operator/(double pt) {

        return Point(x/pt, y/pt, z/pt);
    }


    Point normalize() {
        return *this / sqrt(x*x + y*y + z*z);
    }




};
Point pos(0, 0, -150);
Point u(0,1,0);
Point r(1, 0, 0);
Point l(0, 0, 1);
Point temp(0,0,0);
double tempVal;
int drawaxes;
int x;

//niloy variables
int flag=0;
int q=6;
int s1=10;
int s2=24;
int s3=80;
double angle=0;

//Drawing Triangles inside the spheres
void drawTrianglea(double x){
    //glBegin(GL_POLYGON);
    glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);
	if(flag==0){
	glVertex3f(x,0,-14);
	glVertex3f(-x,-x,-14);
	glVertex3f(-x,x,-14);
	flag=0;
	}
	else if(flag==1){
	glVertex3f(-x,0,-14);
	glVertex3f(x,-x,-14);
	glVertex3f(x,x,-14);
       flag=1;
	}
	glEnd();
}
void drawTriangleb(double x){
        glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);
	if(flag==0){
	glVertex3f(-x,0,-14);
	glVertex3f(x,-x,-14);
	glVertex3f(x,x,-14);
	flag=0;
    }
    else if(flag==1){
    	glVertex3f(x,0,-14);
	glVertex3f(-x,-x,-14);
	glVertex3f(-x,x,-14);
	flag=1;
    }
	glEnd();
}
void drawTrianglec(double x){
    glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);

	if(flag==0){
    glVertex3f(0,x,-12);
	glVertex3f(x,-x,-12);
	glVertex3f(-x,-x,-12);
	flag=0;
	}
	else if(flag==1){
	glVertex3f(-x,x,-12);
	glVertex3f(x,x,-12);
	glVertex3f(0,-x,-12);
	flag=1;
	}
	glEnd();
}
void drawTriangled(double x){

    glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);

    if(flag==0){
    glVertex3f(-x,x,-12);
	glVertex3f(x,x,-12);
	glVertex3f(0,-x,-12);
	flag=0;
    }
    else if(flag==1){
	glVertex3f(0,x,-12);
	glVertex3f(x,-x,-12);
	glVertex3f(-x,-x,-12);
	flag = 1;
    }
	glEnd();
}
void drawSphere(double radius,int slices,int stacks)
{
	Point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}

	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}

}

/*
1 - rotate/look left
2 - rotate/look right
3 - look up
4 - look down
5 - tilt clockwise
6 - tilt counterclockwise
*/
void press1(){
            temp.x = l.x*cos(pi/90) - r.x*sin(pi/90);
            temp.y = l.y*cos(pi/90) - r.y*sin(pi/90);
            temp.z = l.z*cos(pi/90) - r.z*sin(pi/90);
            tempVal = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
            temp.x /= tempVal;
            temp.y /= tempVal;
            temp.z /= tempVal;

            r.x = r.x*cos(pi/90) + l.x*sin(pi/90);
            r.y = r.y*cos(pi/90) + l.y*sin(pi/90);
            r.z = r.z*cos(pi/90) + l.z*sin(pi/90);
            tempVal = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
            r.x /= tempVal;
            r.y /= tempVal;
            r.z /= tempVal;
            l.x = temp.x;
            l.y = temp.y;
            l.z = temp.z;
}

void press2(){
            temp.x = l.x*cos(-pi/90) - r.x*sin(-pi/90);
            temp.y = l.y*cos(-pi/90) - r.y*sin(-pi/90);
            temp.z = l.z*cos(-pi/90) - r.z*sin(-pi/90);
            tempVal = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
            temp.x /= tempVal;
            temp.y /= tempVal;
            temp.z /= tempVal;

            r.x = r.x*cos(-pi/90) + l.x*sin(-pi/90);
            r.y = r.y*cos(-pi/90) + l.y*sin(-pi/90);
            r.z = r.z*cos(-pi/90) + l.z*sin(-pi/90);
            tempVal = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
            r.x /= tempVal;
            r.y /= tempVal;
            r.z /= tempVal;
            l.x = temp.x;
            l.y = temp.y;
            l.z = temp.z;
}

void press3(){
            temp.x = l.x*cos(pi/90) + u.x*sin(pi/90);
            temp.y = l.y*cos(pi/90) + u.y*sin(pi/90);
            temp.z = l.z*cos(pi/90) + u.z*sin(pi/90);
            tempVal = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
            temp.x /= tempVal;
            temp.y /= tempVal;
            temp.z /= tempVal;

            u.x = u.x*cos(pi/90) - l.x*sin(pi/90);
            u.y = u.y*cos(pi/90) - l.y*sin(pi/90);
            u.z = u.z*cos(pi/90) - l.z*sin(pi/90);
            tempVal = sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
            u.x /= tempVal;
            u.y /= tempVal;
            u.z /= tempVal;
            l.x = temp.x;
            l.y = temp.y;
            l.z = temp.z;

}

void press4(){
            temp.x = l.x*cos(-pi/90) + u.x*sin(-pi/90);
            temp.y = l.y*cos(-pi/90) + u.y*sin(-pi/90);
            temp.z = l.z*cos(-pi/90) + u.z*sin(-pi/90);
            tempVal = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
            temp.x /= tempVal;
            temp.y /= tempVal;
            temp.z /= tempVal;

            u.x = u.x*cos(-pi/90) - l.x*sin(-pi/90);
            u.y = u.y*cos(-pi/90) - l.y*sin(-pi/90);
            u.z = u.z*cos(-pi/90) - l.z*sin(-pi/90);
            tempVal = sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
            u.x /= tempVal;
            u.y /= tempVal;
            u.z /= tempVal;
            l.x = temp.x;
            l.y = temp.y;
            l.z = temp.z;
}

void press5(){
            temp.x = r.x*cos(pi/90) - u.x*sin(pi/90);
            temp.y = r.y*cos(pi/90) - u.y*sin(pi/90);
            temp.z = r.z*cos(pi/90) - u.z*sin(pi/90);
            tempVal = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
            temp.x /= tempVal;
            temp.y /= tempVal;
            temp.z /= tempVal;

            u.x = u.x*cos(pi/90) + r.x*sin(pi/90);
            u.y = u.y*cos(pi/90) + r.y*sin(pi/90);
            u.z = u.z*cos(pi/90) + r.z*sin(pi/90);
            tempVal = sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
            u.x /= tempVal;
            u.y /= tempVal;
            u.z /= tempVal;
            r.x = temp.x;
            r.y = temp.y;
            r.z = temp.z;
}

void press6(){

            temp.x = r.x*cos(-pi/90) - u.x*sin(-pi/90);
            temp.y = r.y*cos(-pi/90) - u.y*sin(-pi/90);
            temp.z = r.z*cos(-pi/90) - u.z*sin(-pi/90);
            tempVal = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
            temp.x /= tempVal;
            temp.y /= tempVal;
            temp.z /= tempVal;


            u.x = u.x*cos(-pi/90) + r.x*sin(-pi/90);
            u.y = u.y*cos(-pi/90) + r.y*sin(-pi/90);
            u.z = u.z*cos(-pi/90) + r.z*sin(-pi/90);
            tempVal = sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
            u.x /= tempVal;
            u.y /= tempVal;
            u.z /= tempVal;
            r.x = temp.x;
            r.y = temp.y;
            r.z = temp.z;
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1':
            press2();
			break;
        case '2':
            press1();
			break;
        case '3':
            press3();
			break;
        case '4':
            press4();
			break;
        case '5':
            press5();
			break;
        case '6':
            press6();
			break;
		default:
			break;
	}
}

/*
up arrow - move forward
down arrow - move backward
right arrow - move right
left arrow - move left
PgUp - move up
PgDn - move down
*/
void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			pos.x -= 2.0*l.x;
			pos.y -= 2.0*l.y;
			pos.z -= 2.0*l.z;
			break;
		case GLUT_KEY_UP:		// up arrow key
			pos.x += 2.0*l.x;
			pos.y += 2.0*l.y;
			pos.z += 2.0*l.z;
			break;
		case GLUT_KEY_RIGHT:
			pos.x += 2.0*r.x;
			pos.y += 2.0*r.y;
			pos.z += 2.0*r.z;
			break;
		case GLUT_KEY_LEFT:
			pos.x -= 2.0*r.x;
			pos.y -= 2.0*r.y;
			pos.z -= 2.0*r.z;
			break;
		case GLUT_KEY_PAGE_UP:
		    pos.x += 2.0*u.x;
			pos.y += 2.0*u.y;
			pos.z += 2.0*u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    pos.x -= 2.0*u.x;
			pos.y -= 2.0*u.y;
			pos.z -= 2.0*u.z;
			break;
		case GLUT_KEY_INSERT:
			break;
		case GLUT_KEY_HOME:
           /* squareLength = (squareLength/2) > 0? squareLength-2:squareLength;
            circleRadius = circleRadius < 19? circleRadius+1:circleRadius;*/
			break;
		case GLUT_KEY_END:
		    /*squareLength = (squareLength/2) < 16? squareLength+2:squareLength;
            circleRadius = circleRadius > 0? circleRadius-1:circleRadius;*/
			break;
		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking niil DOWN or UP
				if(angle==0){
                    angle=45;
				}
				else{
                    angle=0;
				}
			}
			break;
		case GLUT_RIGHT_BUTTON:
			//........
                if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				if(angle==0){
                    angle=-45;
				}
				else{
                    angle=0;
				}
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			//........
                if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				if(angle==0){
                    angle=90;
				}
				else{
                    angle=0;
				}
			}
			break;
		default:
			break;
	}
}

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the niloy camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/****************************
	/ Add your objects from here
	****************************/
	//add objects

       //Rotate everything
       glRotatef(angle,0,0,-1);

       //Yellow Line
       glBegin(GL_LINES);{
            glColor3f( 1,1,0);
			glVertex3f( 0,0,0);
			glVertex3f( x,0,0);
		}glEnd();

       //Green Line
       glBegin(GL_LINES);{
            glColor3f( 0,1,0);
			glVertex3f( 0,0,0);
			glVertex3f( -x,0,0);
		}glEnd();

       //Blue Line
       glBegin(GL_LINES);{
            glColor3f( 0,0,1);
			glVertex3f( 0,0,0);
			glVertex3f( 0,-x,0);
		}glEnd();

       //Red Line
       glBegin(GL_LINES);{
            glColor3f( 1,0,0);
			glVertex3f( 0,0,0);
			glVertex3f( 0,x,0);
		}glEnd();


    //Yellow Sphere
    glTranslatef(x,0,0);
    drawTrianglea(q);
    glColor3f(1,1,0);
    drawSphere(s1,s2,s3);
    glTranslatef(-x,0,0);

    //Green Sphere
    glColor3f(0,1,0);
    glTranslatef(-x,0,0);
    drawSphere(s1,s2,s3);
    drawTriangleb(q);
    glTranslatef(x,0,0);

    //Red Sphere
    glColor3f(1,0,0);
    glTranslatef(0,x,0);
    drawSphere(s1,s2,s3);
    drawTrianglec(q);
    glTranslatef(0,-x,0);

    //Blue Sphere
    glColor3f(0,0,1);
    glTranslatef(0,-x,0);
    drawSphere(s1,s2,s3);
    drawTriangled(q);
    glTranslatef(0,x,0);


Sleep(5);
	//ADD this line in the end --- if you use double niloy buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){

	//codes for any changes in Models, Camera
	//angle+=0.5;
	if(flag==0){
        x++;
        if(x>100) flag=1;
	}
	else if(flag==1){
        x--;
        if(x<11) flag=0;
	}

	glutPostRedisplay();
}

void init(){
	//codes for initialization
	angle=0;
	drawaxes=1;
	x=0,flag=0;
	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	//gluPerspective(fovY,	aspect_ratio,	Near, Far);
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio niloy that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle niloy time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
