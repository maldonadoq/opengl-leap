#ifndef _OGL_H_
#define _OGL_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define KEY_ESC 27

const float PI = 3.14159;

extern float mh;
extern float mw;

extern float initx;
extern float inity;

extern int gesture_state;
extern int gesture_idx;

extern float radius;
extern int segm;

int color[3] = {255, 255, 255};

void drawcircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);    
    float x, y, theta;    

    glColor3d(color[0],color[1],color[2]);
    for (int ii = 0; ii < num_segments; ii++){
        theta = 2.0f*3.1415926f*float(ii)/float(num_segments);
        x = r*cosf(theta);
        y = r*sinf(theta);
        glVertex2d(x+cx, y+cy);
    }
    glEnd();
}

void glswitch(int _gesture_idx, int _gesture_state){
	switch(_gesture_idx){
		case 0:{
			if(_gesture_state>0 and radius>10) radius-=5;
			else if(_gesture_state<0 and radius<200) radius+=5;
			break;
		}
		case 1:{
			if(_gesture_state < 0)	inity-=10;
			else if(_gesture_state > 0)	inity+=10;
			break;
		}
		case 2:
			break;
		case 3:
			break;
		case 4:{			
			srand(time(NULL));  
			color[0] = rand()%106;
			color[1] = rand()%106;
			color[2] = rand()%106;
			break;
		}
		default:
			break;
	}
}

void glpaint(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-mw,mw,-mh,mh, -1.0f, 1.0f);

	glswitch(gesture_idx, gesture_state);
	drawcircle(initx,inity,radius,segm);	

	gesture_idx = -1;
	gesture_state = 0;
	glutSwapBuffers();
}

void idle(){	glutPostRedisplay();	}

void init_GL(void) {	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-mw,mw,-mh,mh, -1.0f, 1.0f);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
		case KEY_ESC:
			exit(0);
			break;
		default:
			break;
	}
}

#endif