#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

GLsizei winWidth = 400, winHeight = 300;

class screenPt
{
private:
	GLint x, y;
public:
	/* Default Constructor: initializes coordinate position to (0, 0). */
	screenPt ( ) {
		x = y = 0;
	}
	void setCoords (GLint xCoordValue, GLint yCoordValue) {
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx ( ) const {
		return x;
	}
	GLint gety ( ) const {
		return y;
	}
	void incrementx ( ) {
		x++;
	}
	void decrementy ( ) {
		y--;
	}
};

void setPixel (GLint xCoord, GLint yCoord)
{
	glBegin (GL_POINTS);
		glVertex2i (xCoord, yCoord);
	glEnd ( );
}

void circleMidpoint (GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;
	GLint p = 1 - radius; // Initial value for midpoint parameter.
	circPt.setCoords (0, radius); // Set coordinates for top point of circle.
	void circlePlotPoints (GLint, GLint, screenPt);
	/* Plot the initial point in each circle quadrant. */
	circlePlotPoints (xc, yc, circPt);
	/* Calculate next point and plot in each octant. */
	while (circPt.getx ( ) < circPt.gety ( )) {
		circPt.incrementx ( );
		if (p < 0)
			p += 2 * circPt.getx ( ) + 1;
		else {
			circPt.decrementy ( );
			p += 2 * (circPt.getx ( ) - circPt.gety ( )) + 1;
		}
		circlePlotPoints (xc, yc, circPt);
	}
}

void circlePlotPoints (GLint xc, GLint yc, screenPt circPt)
{
	setPixel (xc + circPt.getx ( ), yc + circPt.gety ( ));
	setPixel (xc - circPt.getx ( ), yc + circPt.gety ( ));
	setPixel (xc + circPt.getx ( ), yc - circPt.gety ( ));
	setPixel (xc - circPt.getx ( ), yc - circPt.gety ( ));
	setPixel (xc + circPt.gety ( ), yc + circPt.getx ( ));
	setPixel (xc - circPt.gety ( ), yc + circPt.getx ( ));
	setPixel (xc + circPt.gety ( ), yc - circPt.getx ( ));
	setPixel (xc - circPt.gety ( ), yc - circPt.getx ( ));
}

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0); // White display window.
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 600.0, 0.0, 500.0);
}

void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
	glColor3f (0.0, 0.0, 1.0); // Set circle color to blue.
	circleMidpoint (150, 150, 100);
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
	glutCreateWindow ("Algorithm - Midpoint Circle");
	init ( );
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (winReshapeFcn);
	glutMainLoop ( );
	return EXIT_SUCCESS;
}