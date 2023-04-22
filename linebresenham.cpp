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

/* Bresenham line-drawing procedure for |m| < 1.0. */
void lineBres (int x0, int y0, int xEnd, int yEnd)
{
	int dx = fabs (xEnd - x0);
	int dy = fabs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy;
	int twoDyMinusDx = 2 * (dy - dx);
	int x;
	int y;
	/* Determine which endpoint to use as start position. */
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else {
		x = x0;
		y = y0;
	}
	setPixel (x, y);
	while (x < xEnd) {
		x++;
		if (p < 0) {
			p += twoDy;
		}
		else {
			y++;
			p += twoDyMinusDx;
		}
		setPixel (x, y);
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
	lineBres ( 130, 50, 300, 275);
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
	glutCreateWindow ("Algorithm - Line Bresenham");
	init ( );
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (winReshapeFcn);
	glutMainLoop ( );
	return EXIT_SUCCESS;
}