/* Chris Milson April 2017
** Dragon Curve
*
* This is an OpenGL replica of the processing program I wrote beforehand.
*
* It draws iterations of the dragon curve.
*/
#include "dragonCurve.h"

void processKey(unsigned char key, int x, int y) {
  if (key == 's') {
    descend();
    draw();
  }
  if (key == 'w') {
    ascend();
    draw();
  }
  if (key == 'd') {
    printf("Current depth is %d.\n", depth);
  }
  // Exit on escape key press.
  if (key == 27) {
    exit(0);
  }
}

void ascend() {
  if (depth <= 0) return;
  depth--;

  int i;
  Line *newCurve;
  newCurve = (Line *) malloc(sizeof(Line) * power(2, depth));

  for (i = 0; i < power(2, depth); i++) {
    struct vector start, end;

    start = curve[2 * i].start;
    end = curve[2 * i + 1].start;

    newCurve[i].start = start;
    newCurve[i].end = end;
    newCurve[i].startDepth = curve[2 * i].startDepth;
    newCurve[i].endDepth = curve[2 * i + 1].startDepth;
  }

  free(curve);
  curve = newCurve;
}

void descend() {
  depth++;

  int i;
  Line *newCurve;
  newCurve = (Line *) malloc(sizeof(Line) * power(2, depth));

  for (i = 0; i < power(2, depth - 1); i++) {
    struct vector start, middle, end;

    start = curve[i].start;
    end = curve[i].end;

    middle.x = end.x - start.x;
    middle.y = end.y - start.y;

    // Rotate by pi/4 radians using the rotation matrix, and scale by 1/sqrt(2).
    // simplifies to this.
    middle.x = (middle.x - middle.y) / 2;
    middle.y = (middle.x + middle.y);

    middle.x += start.x;
    middle.y += start.y;

    newCurve[2*i].start = start;
    newCurve[2*i].end = middle;
    newCurve[2*i].startDepth = curve[i].startDepth;
    newCurve[2*i].endDepth = 1.0 * (rand() % 40 - 20) / 50;

    newCurve[2*i + 1].start = end;
    newCurve[2*i + 1].end = middle;
    newCurve[2*i + 1].startDepth = curve[i].endDepth;
    newCurve[2*i + 1].endDepth = newCurve[2*i].endDepth;
  }

  free(curve);
  curve = newCurve;
}

int power(int b, int e) {
  int answer = 1;
  int i;
  for (i = 0; i < e; i++) {
    answer *= b;
  }
  return answer;
}

void changeSize(int w, int h) {
  // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;
	float ratio = 1.0 * w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

  // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float angle = -10.0;

void draw() {
  int i;
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(
  	0.0f, 3.0f, 20.0f,
    0.0f, 1.0f,  0.0f,
    0.0f, 1.0f,  0.0f
  );

  glRotatef(angle, 0, 1, 0);

  glLineWidth(2);
  glColor3f(1, 1, 1);

  for (i = 0; i < power(2, depth); i++) {
    glBegin(GL_LINES);
      glVertex3f(curve[i].start.x, curve[i].start.y, curve[i].startDepth);
      glVertex3f(curve[i].end.x, curve[i].end.y, curve[i].endDepth);
    glEnd();
  }

  angle += 0.1f;

  glutSwapBuffers();
}


int main(int argc, char **argv) {
  int i;
  // Initialise GLUT
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutCreateWindow("Dragon Curve - OpenGL");

  // Initialise Global variables
  depth = 0;
  struct vector start, end;
  start.x = -4.0;
  start.y = 0;

  end.x = 4.0;
  end.y = 0;

  curve = (Line *) malloc(sizeof(Line) * power(2, depth));
  curve[0].start = start;
  curve[0].end = end;
  curve[0].startDepth = curve[0].endDepth = 0;

  for (i = 0; i < 11; i++) {
    descend();
  }

  // register callbacks
  glutDisplayFunc(draw);
  glutReshapeFunc(changeSize);
  glutKeyboardFunc(processKey);
  glutIdleFunc(draw);

  // Start
  glutMainLoop();

  return 0;
}
