#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <vector>

#define PI 3.141592653589793

#define kWindowHeight 600.0
#define kWindowWidth 800.

GLint keyStates[256];

typedef struct vector2d { GLdouble x, y; } VECTOR2D;
typedef struct point2d { GLdouble x, y; } POINT2D;
typedef struct circle {
    GLdouble x, y,r;
    GLdouble speedX,speedY;
    GLint counter;
    GLint part;
    GLint active;

} CIRCLE;


CIRCLE circles[200];

VECTOR2D linearVector;
VECTOR2D normalVector;


double lineEquation;

double horizontalStartX = kWindowWidth/2;
double horizontalStartY = kWindowHeight-1;
double horizontalEndX = kWindowWidth/2;
double horizontalEndY = 0;

double verticalStartX = 0;
double verticalStartY = kWindowHeight/2;
double verticalEndX = kWindowWidth-1;
double verticalEndY = kWindowHeight/2;
int circleCounter = 0;
int timeCounter = 1;
void display();
void drawHorizontalBorder(double, double,double, double);
void drawVerticalBorder(double, double,double, double);
void init();
int getSideFromLine(POINT2D , POINT2D , POINT2D );
POINT2D initPoint2D(GLdouble, GLdouble);
CIRCLE initCircle(GLdouble , GLdouble , double);
void horizontalMoveMinus();
void horizontalMovePositive();
void verticalMoveMinus();
void verticalMovePositive();
void showBubbles();
void circle(POINT2D, GLdouble);
void processMouse( GLint , GLint , GLint  , GLint  );
int getPart(GLdouble, GLdouble);
double distancePointFromLine(POINT2D ,POINT2D ,POINT2D );
int getNextCirclePlace();

void drawCircle(CIRCLE circle_) {

	glBegin(GL_POLYGON);
	for (GLdouble t = 0; t <= 2 * PI; t += 0.01)
		glVertex2d(circle_.x + circle_.r * cos(t), circle_.y + circle_.r * sin(t));
	glEnd();


}

POINT2D initPoint2D(GLdouble x, GLdouble y) {
	POINT2D P;
	P.x = x;
	P.y = y;
	return P;
}

CIRCLE initCircle(GLdouble x, GLdouble y, double r) {
    double speed = rand() % 1000 + 1;
    speed /= 1000;
	CIRCLE c;
	c.x = x;
	c.y = y;
	c.r = r;
	c.part = getPart(c.x, c.y);
	c.speedX = speed;
	c.speedY = speed;
	c.active = 1;
	//printf("init circle : %d\n", c.r);
	return c;
}

void horizontalMoveMinus(){
    if(horizontalStartX<=0){
    }else if(horizontalEndX>=kWindowWidth-1){
    }else{
        horizontalStartX-=0.4;
        horizontalEndX+=0.4;
    }
}

void horizontalMovePositive(){

    if(horizontalStartX>=kWindowWidth-1){
    }else if(horizontalEndX<=0){
    }else{
        horizontalEndX-=0.4;
        horizontalStartX+=0.4;
    }
}

void verticalMoveMinus(){


    if(verticalStartY <= 0){
    }else{
        verticalStartY-=0.4;
        verticalEndY+=0.4;
    }
}

void verticalMovePositive(){
    if(verticalStartY >= kWindowHeight-1){
    }else{
        verticalStartY+=0.4;
        verticalEndY-=0.4;
    }


}

void keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void keyOperations ( ) {
    if (keyStates['a']) {	horizontalMoveMinus(); }

    if (keyStates['d']) {  horizontalMovePositive();
    }

    if (keyStates['s']) {	verticalMoveMinus(); }
    if (keyStates['w']) {   verticalMovePositive(); }


    glutPostRedisplay( );
}

void init( ) {
    glClearColor ( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode ( GL_PROJECTION );
    gluOrtho2D ( 0.0, kWindowWidth-1, 0.0, kWindowHeight-1 );
    glShadeModel ( GL_FLAT );
    glEnable( GL_POINT_SMOOTH );
    glPointSize( 5.0 );
     glLineWidth( 3.0 );
}

void drawHorizontalBorder(double startX, double starY, double endX, double endY){

    glBegin (GL_LINES);
        glVertex2i (startX, starY);
        glVertex2i (endX, endY);
    glEnd ( );

}

void drawVerticalBorder(double startX, double starY, double endX, double endY){

    glBegin (GL_LINES);
        glVertex2i (startX, starY);
        glVertex2i (endX, endY);
    glEnd ( );

}
void showBubbles(){

    glBegin( GL_POINTS );
        for ( double i = 0; i < kWindowWidth-1; i=i+10 ){
            for (double  j = kWindowHeight-1; j > 0; j=j-10 ){
                    int side = 0;
                    side = getSideFromLine(initPoint2D(horizontalStartX, horizontalStartY), initPoint2D(horizontalEndX, horizontalEndY),initPoint2D(i,j));
                    side*=2;
                    side += getSideFromLine(initPoint2D(verticalStartX, verticalStartY), initPoint2D(verticalEndX, verticalEndY),initPoint2D(i,j));
                    if(side==-3){
                        glColor3f(1.0, 0.1, 1.0);
                    }else if(side==-1){
                        glColor3f(1.0, 0.8, 1.0);
                    }else if(side==1){
                        glColor3f(0.0, 0.6, 0.5);
                    }else if(side==3){
                        glColor3f(0.5, 0.6, 0.1);
                    }else{
                        glColor3f(0.0, 1.0, 1.0);
                    }
                    glVertex2f( i, j );
            }
        }
    glEnd( );
}

VECTOR2D getLinerVector(double startX,double startY,double endX,double endY){
    VECTOR2D linearVector_;
    linearVector_.x = endX-startX;
    linearVector_.y = endY-startY;
    return linearVector_;
}

VECTOR2D getNormalVector(VECTOR2D linearVector){
    VECTOR2D normalVector;
    double tmp;
    tmp = normalVector.x;
    normalVector.x = normalVector.y;
    normalVector.y = tmp*-1;
    return normalVector;
}

int isPointOnLine(POINT2D point, VECTOR2D normalVector, double lineEquation ){
    if(normalVector.x*point.x+normalVector.y*point.y==lineEquation){
        return 1;
    }
    return 0;
}

double getLineEquation(VECTOR2D normalVector, double x, double y){
    return lineEquation = normalVector.x*x+normalVector.y*y;
}

int getSideFromLine(POINT2D point1, POINT2D point2, POINT2D queryPoint){
        double tmp = ((point1.x-point2.x)*(queryPoint.y-point2.y)-(point1.y-point2.y)*(queryPoint.x-point2.x));
        if(tmp<0){
            return 1;
        }else if(tmp>0){
            return -1;
        }else{
            return 0;
        }
}

void display( )
{
    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    showBubbles();
    glColor3f(0.0, 0.0, 1.0);
    drawHorizontalBorder(horizontalStartX, horizontalStartY, horizontalEndX, horizontalEndY);
    drawVerticalBorder(verticalStartX, verticalStartY, verticalEndX, verticalEndY);

    if(circleCounter){
        for(int i=0; i<circleCounter;i++){
                if(circles[i].active){
                    drawCircle(circles[i]);
                }

            //printf("\n %d . sor %f", circleCounter,circles[circleCounter].y);
            //printf("sorszam: %d\n %f",i,circles[i].x);

        }
    }

    glutSwapBuffers();
}

POINT2D mirroring(POINT2D wannabe_mirrored,POINT2D mirror)
{
  /*GLint proj_b_a_mul_2=(wannabe_mirrored.x*mirror.x + wannabe_mirrored.y*mirror.y)*2/(mirror.x*mirror.x+mirror.y*mirror.y);
  return initPoint2D(mirror.x*proj_b_a_mul_2-wannabe_mirrored.x,mirror.y*proj_b_a_mul_2-wannabe_mirrored.y); */
  GLfloat tmp=(wannabe_mirrored.x*mirror.x + wannabe_mirrored.y*mirror.y)/(mirror.x*mirror.x + mirror.y*mirror.y);
  POINT2D C={mirror.x*tmp,mirror.y*tmp};
  POINT2D AC={C.x-wannabe_mirrored.x,C.y-wannabe_mirrored.y};
  POINT2D mirrored={wannabe_mirrored.x+2*AC.x,wannabe_mirrored.y+2*AC.y};
  return mirrored;
}

void changeSpeed(CIRCLE circle_, POINT2D mirrorPoint, int counter){
    POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circle_.speedX, circle_.speedY);
            tmpVector=mirroring(actVector,initPoint2D(mirrorPoint.x,mirrorPoint.y));
            circles[counter].speedX = tmpVector.x;
            circles[counter].speedY = tmpVector.y;
}

void update(int n)
{
    for(int i=0; i<circleCounter;i++){
        if(circles[i].active){
        circles[i].x+=circles[i].speedX;
        circles[i].y+=circles[i].speedY;

        if(circles[i].part==2){
            if(round(distancePointFromLine(initPoint2D(horizontalStartX, horizontalStartY), initPoint2D(horizontalEndX, horizontalEndY), initPoint2D(circles[i].x, circles[i].y)))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(horizontalStartX-horizontalEndX, horizontalStartY-horizontalEndY), i);
        }
        if(round(distancePointFromLine(initPoint2D(verticalStartX, verticalStartY), initPoint2D(verticalEndX, verticalEndY), initPoint2D(circles[i].x, circles[i].y)))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(verticalStartX-verticalEndX, verticalStartY-verticalEndY), i);
        }
        if(round(distancePointFromLine(initPoint2D(0, 0), initPoint2D(0, kWindowHeight/2), initPoint2D(circles[i].x, circles[i].y)))<=round(30.0)){
             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(0-0,0-kWindowHeight/2));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        if(round(distancePointFromLine(initPoint2D(0, 0), initPoint2D(kWindowWidth/2, 0), initPoint2D(circles[i].x, circles[i].y)))>=round(-30.0)){
             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(0-kWindowWidth/2,0-0));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        }else if(circles[i].part==0){
            if(fabs(round(distancePointFromLine(initPoint2D(horizontalStartX, horizontalStartY), initPoint2D(horizontalEndX, horizontalEndY), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(horizontalStartX-horizontalEndX, horizontalStartY-horizontalEndY), i);
        }
        if(fabs(round(distancePointFromLine(initPoint2D(verticalStartX, verticalStartY), initPoint2D(verticalEndX, verticalEndY), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(verticalStartX-verticalEndX, verticalStartY-verticalEndY), i);
        }
        if(fabs(round(distancePointFromLine(initPoint2D(0, kWindowHeight-1), initPoint2D(kWindowWidth/2, kWindowHeight-1), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(0-kWindowWidth/2,kWindowHeight-1-kWindowHeight-1));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        if(fabs(round(distancePointFromLine(initPoint2D(0, kWindowHeight-1), initPoint2D(0, kWindowHeight/2), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){
             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(0-0,kWindowHeight-1-kWindowHeight/2));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        }else if(circles[i].part==1){
            if(fabs(round(distancePointFromLine(initPoint2D(horizontalStartX, horizontalStartY), initPoint2D(horizontalEndX, horizontalEndY), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(horizontalStartX-horizontalEndX, horizontalStartY-horizontalEndY), i);
        }
        if(fabs(round(distancePointFromLine(initPoint2D(verticalStartX, verticalStartY), initPoint2D(verticalEndX, verticalEndY), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(verticalStartX-verticalEndX, verticalStartY-verticalEndY), i);
        }
        if(fabs(round(distancePointFromLine(initPoint2D(kWindowWidth/2, kWindowHeight-1), initPoint2D(kWindowWidth-1, kWindowHeight-1), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(kWindowWidth/2-kWindowWidth-1,kWindowHeight-1-kWindowHeight-1));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        if(fabs(round(distancePointFromLine(initPoint2D(kWindowWidth-1, kWindowHeight-1), initPoint2D(kWindowWidth-1, kWindowHeight/2), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){
             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(kWindowWidth-1-kWindowWidth-1,kWindowHeight-1-kWindowHeight/2));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        }else if(circles[i].part==3){
            if(fabs(round(distancePointFromLine(initPoint2D(horizontalStartX, horizontalStartY), initPoint2D(horizontalEndX, horizontalEndY), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(horizontalStartX-horizontalEndX, horizontalStartY-horizontalEndY), i);
        }
        if(fabs(round(distancePointFromLine(initPoint2D(verticalStartX, verticalStartY), initPoint2D(verticalEndX, verticalEndY), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){

            changeSpeed(circles[i], initPoint2D(verticalStartX-verticalEndX, verticalStartY-verticalEndY), i);
        }
        if(fabs(round(distancePointFromLine(initPoint2D(kWindowWidth-1, kWindowHeight/2), initPoint2D(kWindowWidth-1, 0), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){
             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(kWindowWidth-1-kWindowWidth-1,kWindowHeight/2-0));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        if(fabs(round(distancePointFromLine(initPoint2D(kWindowWidth/2, 0), initPoint2D(kWindowWidth-1, 0), initPoint2D(circles[i].x, circles[i].y))))<=round(30.0)){
             POINT2D tmpVector;
            POINT2D actVector = initPoint2D(circles[i].speedX, circles[i].speedY);
            tmpVector=mirroring(actVector,initPoint2D(kWindowWidth/2-kWindowWidth-1,0-0));
            circles[i].speedX = tmpVector.x;
            circles[i].speedY = tmpVector.y;

        }
        }


    }
    }
   glutPostRedisplay( );

        glutTimerFunc( 5, update, 1 );
}

double distancePointFromLine(POINT2D linePoint1,POINT2D linePoint2,POINT2D point)
{
    //printf("%f\n",( (linePoint1.y-linePoint2.y)*linePoint1.x + (linePoint2.x-linePoint1.x)*linePoint1.y - (linePoint1.y-linePoint2.y)*point.x - (linePoint2.x-linePoint1.x)*point.y)/sqrt((linePoint1.y-linePoint2.y)*(linePoint1.y-linePoint2.y) + (linePoint2.x-linePoint1.x)*(linePoint2.x-linePoint1.x)));
    return ( (linePoint1.y-linePoint2.y)*linePoint1.x + (linePoint2.x-linePoint1.x)*linePoint1.y - (linePoint1.y-linePoint2.y)*point.x - (linePoint2.x-linePoint1.x)*point.y)/sqrt((linePoint1.y-linePoint2.y)*(linePoint1.y-linePoint2.y) + (linePoint2.x-linePoint1.x)*(linePoint2.x-linePoint1.x));
}

void processMouse( GLint button, GLint action, GLint xMouse , GLint yMouse ) {
    GLint i;
    if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN ){
            int nextCirclePlace = getNextCirclePlace();
            printf("1 %d\n",circleCounter);
            if(nextCirclePlace!=-1){
                  //  printf("2 %d\n",circleCounter);
                 CIRCLE tmpCircle = initCircle(xMouse, kWindowHeight-yMouse, 30.0);
//printf("3 %d\n",circleCounter);
                circles[nextCirclePlace] = tmpCircle;
             //   printf("4%d\n",circleCounter);
                drawCircle(circles[nextCirclePlace]);
               // printf("5 %d",circleCounter);
                if(nextCirclePlace == circleCounter){
                    circleCounter++;
                }
                if(timeCounter)
                update(1);
                timeCounter = 0;
                }
        }
    if ( button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN  ){
            printf("pushed");
            for(int i=0;i<circleCounter;i++){
                if((circles[i].x - circles[i].r<= xMouse && circles[i].x + circles[i].r>= xMouse) && (circles[i].y - circles[i].r<= kWindowHeight-yMouse && circles[i].y + circles[i].r>= kWindowHeight-yMouse)){

                    circles[i].active = 0;
                }
            }
    }

}

int getPart(GLdouble x, GLdouble y){//-3:1 -1:2 1:3 3:4
    int side;
    side = getSideFromLine(initPoint2D(horizontalStartX, horizontalStartY), initPoint2D(horizontalEndX, horizontalEndY),initPoint2D(x,y));
    side*=2;
    side += getSideFromLine(initPoint2D(verticalStartX, verticalStartY), initPoint2D(verticalEndX, verticalEndY),initPoint2D(x,y));
    if(side==-3){ //bottom left
        side = 2;
    }else if(side==-1){//top left
        side = 0;
    }else if(side==1){   //bottom right
        side = 3;
    }else if(side==3){
        side = 1;   //top right
    }else{
        //printf("Something wrong in getPart()");
    }
    return side;
}

int getNextCirclePlace(){


    int i;
    for(i=0;i<circleCounter;i++){
        if(!circles[i].active){
            return i;
        }
    }

    if(i==21){
        return -1;
    }
    if(i==circleCounter){
        return circleCounter;
    }

}
int main(int argc, char** argv)
{
   glutInit( &argc, argv );
   glutInitDisplayMode( GLUT_DOUBLE  | GLUT_RGB );
   glutInitWindowSize( kWindowWidth, kWindowHeight );
   glutInitWindowPosition ( 0, 0 );
   glutCreateWindow( "Hazi feladat 1" );
   srand (time(NULL));
   init( );
   glutDisplayFunc( display );
   glutKeyboardFunc(keyPressed);
   glutKeyboardUpFunc(keyUp);
   glutMouseFunc( processMouse );
   glutMainLoop( );
   return 0;
}
