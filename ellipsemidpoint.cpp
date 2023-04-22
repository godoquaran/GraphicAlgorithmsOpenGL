#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>

inline int round (const float a) { return int (a + 0.5); }

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

/* The following procedure accepts values for an ellipse
* center position and its semimajor and semiminor axes, then
* calculates ellipse positions using the midpoint algorithm.
*/
void ellipseMidpoint (int xCenter, int yCenter, int Rx, int Ry)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;
	void ellipsePlotPoints (int, int, int, int);
	/* Plot the initial point in each quadrant. */
	ellipsePlotPoints (xCenter, yCenter, x, y);
	/* Region 1 */
	p = round (Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0)
		p += Ry2 + px;
		else {
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoints (xCenter, yCenter, x, y);
	}
	/* Region 2 */
	p = round (Ry2 * (x+0.5) * (x+0.5) + Rx2 * (y-1) * (y-1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0)
		p += Rx2 - py;
		else {
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints (xCenter, yCenter, x, y);
	}
}

void ellipsePlotPoints (int xCenter, int yCenter, int x, int y)
{
	setPixel (xCenter + x, yCenter + y);
	setPixel (xCenter - x, yCenter + y);
	setPixel (xCenter + x, yCenter - y);
	setPixel (xCenter - x, yCenter - y);
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
	ellipseMidpoint (150, 150, 100, 75);
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
	glutCreateWindow ("Algorithm - Ellipse Midpoint");
	init ( );
	glutDisplayFunc (displayFcn);
	glutReshapeFunc (winReshapeFcn);
	glutMainLoop ( );
	return EXIT_SUCCESS;
}