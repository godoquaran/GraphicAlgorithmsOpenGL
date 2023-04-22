#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

inline int round (const float a) { return int (a + 0.5); }

GLsizei winWidth = 400, winHeight = 300;

void setPixel (GLint xCoord, GLint yCoord)
{
	glBegin (GL_POINTS);
		glVertex2i (xCoord, yCoord);
	glEnd ( );
}

void lineDDA (int x0, int y0, int xEnd, int yEnd)
{
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	int steps;
	int k;
	float xIncrement;
	float yIncrement;
	float x = x0;
	float y = y0;
	if (fabs (dx) > fabs (dy)) {
		steps = fabs (dx);
	}
	else {
		steps = fabs (dy);
	}
	xIncrement = float (dx) / float (steps);
	yIncrement = float (dy) / float (steps);
	setPixel (round (x), round (y));
	for (k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		setPixel (round (x), round (y));
	}
}

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 1.0); 
	lineDDA ( 130, 50, 300, 275);
	glFlush ( );
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
	glClear (GL_COLOR_BUFFER_BIT);
	/* Reset display-window size parameters. */
	winWidth = newWidth;
	winHeight = newHeight;	
}

int main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Algorithm - Line DDA");
	init ( );
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (winReshapeFcn);
	glutMainLoop ( );
	return EXIT_SUCCESS;
}