#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include "objloader.h"
//#include <iostream>
#include <stdlib.h>

using namespace std;


//global variables
const char programTitle[] = "Pong (Im-pong-sible)";
const int windowWidth = 800;
const int windowHeight = 600;

bool p2 = false;

static float xo = 0;
static float yo = 0;
float p1yo = 0;
float p1len = 7;
float p2yo = 0;
float p2len = 7;

bool up = true;
bool lft = true;

static float deltay = .1;
static float deltax = .25;


void display(void);

float abs(float a);

void ballGo(void);

void init (void);

void reshape(int w, int h);

void SpecialInput(int key, int x, int y);

void restart (unsigned char key, int xmouse, int ymouse);

int main(int argc, char** argv) {

    /* glutInit() - Before any other GLUT routine */
    glutInit(&argc, argv);

    /* glutInitDisplayMode() - RGBA or color-index model / 
        single or double buffered window */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (windowWidth, windowHeight);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (programTitle);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
//    glutMouseFunc(mouse);
		glutIdleFunc(ballGo);
		glutSpecialFunc(SpecialInput);
		glutKeyboardFunc(restart);
    glutMainLoop();
    return 0;
}

void display(void)
{
    /* clear all pixels */
    glClear (GL_COLOR_BUFFER_BIT);
	
    glPushMatrix();

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f( 48,  p1len + p1yo, 0);
        glVertex3f( 48, -p1len + p1yo, 0);
        glVertex3f( 45, -p1len + p1yo, 0);
		glVertex3f( 45,  p1len + p1yo, 0);
		glEnd();

	if(!p2)
	{
		glBegin(GL_QUADS);
        glVertex3f( -48,  47, 0);
        glVertex3f( -48, -47, 0);
        glVertex3f( -45, -47, 0);
				glVertex3f( -45,  47, 0);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
        glVertex3f( -48,  p2len + p2yo, 0);
        glVertex3f( -48, -p2len + p2yo, 0);
        glVertex3f( -45, -p2len + p2yo, 0);
		glVertex3f( -45,  p2len + p2yo, 0);
		glEnd();
	}
		glBegin(GL_QUADS);
        glVertex3f( 2 + xo, -2 + yo, 0);
        glVertex3f(-2 + xo, -2 + yo, 0);
        glVertex3f(-2 + xo,  2 + yo, 0);
		glVertex3f( 2 + xo,  2 + yo, 0);
		glEnd();

		glPopMatrix();

    glutSwapBuffers();
}

float abs(float a)
{
	if(a < 0)
		return -a;
	else
		return a;
}

void ballGo(void)
{
	float margin;
	
	// up and down
	if(up)
	{
		yo += deltay;
		if(yo >= 47)
			up = false;
	}
	else
	{
		yo -= deltay;
		if(yo <= -47)
			up = true;
	}
	
	// left and right
	if(lft)
	{
		xo -= deltax;
		if(xo <= -43 && xo >= -44)
		{
			if(!p2)
				lft = false;
			else
			{
				margin = abs(p2yo - yo);
				if(margin <= p2len)
				{				
					lft = false;
					if(margin <= 1)
						deltay = .1;
					else if(margin <= 3)
						deltay = .2;
					else if(margin <= 5)
						deltay = .3;
					else
						deltay = .4;
				}
			}
		}
	}
	else
	{
		xo += deltax;
		if(xo >= 43 && xo <= 44)
		{
			margin = abs(p1yo - yo);
			if(margin <= p1len)
			{				
				lft = true;
				if(margin <= 1)
					deltay = .1;
				else if(margin <= 3)
					deltay = .2;
				else if(margin <= 5)
					deltay = .3;
				else
					deltay = .4;
			}
		}
	}
		
	glutPostRedisplay();
}

void init (void)
{
    /* select clearing (background) color*/
    glClearColor (0.0, 0.0, 0.0, 0.0);
    /*initialize viewing values */
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if(p1yo < 45)
				p1yo += 5;
			else
				p1yo = -45;
			break;
		
		case GLUT_KEY_DOWN:
			if(p1yo > -45)
				p1yo -= 5;
			else 
				p1yo = 45;
			break;

		case GLUT_KEY_LEFT:
			if(deltax > .02)
				deltax -= .05;
			break;

		case GLUT_KEY_RIGHT:
			if(deltax < .8)
				deltax += .05;
			break;

		default:
			break;
	}

	glutPostRedisplay();
} 

void restart (unsigned char key, int xmouse, int ymouse)
{	
	switch (key){
		case 'r':
			xo = 0;
			yo = 0;
			lft = true;
			deltay = .2;

			break;
		case 'p':
			if(p2)
				p2 = false;
			else
				p2 = true;
			break;
		case 'w':
			p2yo += 5;
			if(p2yo == 45)
				p2yo = -45;
			break;

		case 's':
            p2yo -= 5;
            if(p2yo == -45)
                p2yo = 45;
            break;

        case 'e':
            p1len++;    
            p2len++;    
            break;

        case 'h':
            p1len--;
            p2len--;    
            break;



		case 'q':
			exit(1);
			break;
		default:
			break;
	
		
	}
	
	glutPostRedisplay();
}

