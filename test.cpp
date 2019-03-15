#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstring>

#include "Leap.h"
#include "usr/listener.h"
#include "usr/ogl.h"

float initx = 0;
float inity = 0;

float hwin = 400;
float wwin = 600;

float mh = hwin/2;
float mw = wwin/2;

int gesture_idx = -1;
/*
    -1 = unknown
    0 = circle
    1 = swipe
    2 = key tap
    3 = screen tap
    4 = fist
*/
int gesture_state = 0;

float radius = 50;  // circle
int segm = 50;      // circle's segment

using namespace Leap;

int main(int argc, char *argv[]){   
    TListener listener;
    Controller controller;

    controller.addListener(listener);  
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(wwin, hwin);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Leap");
    init_GL();

    glutDisplayFunc(glpaint);

    glutReshapeFunc(&window_redraw);
    glutKeyboardFunc(&window_key);
    glutIdleFunc(&idle);

    glutMainLoop();

    controller.removeListener(listener);
    return 0;
}

// sudo leapd
// LeapControlPanel
