#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void draw(void);
void changeSize(int width, int height);
int power(int base, int exponent);
void descend(void);
void ascend(void);
void processKey(unsigned char key, int x, int y);

struct vector {
  float x;
  float y;
};

typedef struct Line{
  struct vector start;
  struct vector end;
} Line;

int depth;
Line *curve;
