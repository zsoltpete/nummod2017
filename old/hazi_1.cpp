#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct point2d { GLfloat x, y; } POINT2D;

GLfloat Move=1;
GLsizei winWidth = 1024, winHeight = 768;
POINT2D up={winWidth/2,winHeight};
POINT2D down={winWidth/2,0};
POINT2D right={winWidth,winHeight/2};
POINT2D left={0,winHeight/2};
//POINT2D mid={400,300};
GLdouble CIRCLE_R=35;
POINT2D circle_points[20];
POINT2D VECTOR[20];
GLint circle_count=0;
GLfloat elozo=0;
POINT2D polygon_points[10];
GLint sides[20];
GLint keyStates[256];


POINT2D initPoint2D( GLint x, GLint y ) {
    POINT2D P;
    P.x = x;
    P.y = y;
    return P;
}

POINT2D initPoint2D( GLdouble x, GLdouble y ) {
    POINT2D P;
    P.x = x;
    P.y = y;
    return P;
}



void circle(POINT2D O, GLdouble r) 
{
    glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	for (GLdouble t = 0; t <= 2 * M_PI; t += 0.4)
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	glEnd();
}

void polygon(POINT2D O, GLdouble r,GLint sides) {
	glLineWidth( 1.5 );
	GLint i=0,j;
	glColor3f( 0.0, 0.0, 0.0 );
	glBegin(GL_LINE_LOOP);
	for (GLdouble t = 0; t <= 2*M_PI; t += (2*M_PI/sides))
	{
		polygon_points[i]=initPoint2D(O.x + r * cos(t), O.y + r * sin(t));
		glVertex2d(polygon_points[i].x,polygon_points[i].y);
		i++;
	}
	glEnd();
	glBegin(GL_LINES);
	  for(i=0;i<sides-1;i++)
	    for(j=0;j<sides-3 && i+j+2<sides;j++)
	    {
	      glVertex2d(polygon_points[i].x,polygon_points[i].y);
	      glVertex2d(polygon_points[i+j+2].x,polygon_points[i+j+2].y);
	    }
      glEnd();
}

GLfloat dist2( POINT2D P1, POINT2D P2 ) {
    GLfloat t1 = P1.x - P2.x;
    GLfloat t2 = P1.y - P2.y;
    return t1 * t1 + t2 * t2;
}

GLfloat dist_point_to_line(POINT2D A,POINT2D B,POINT2D P)
{
 return ( (A.y-B.y)*A.x + (B.x-A.x)*A.y - (A.y-B.y)*P.x - (B.x-A.x)*P.y)/sqrt((A.y-B.y)*(A.y-B.y) + (B.x-A.x)*(B.x-A.x));
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

void init( ) {
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, winWidth, 0.0, winHeight );
    glShadeModel( GL_FLAT );
    glEnable( GL_POINT_SMOOTH );
    //glEnable(GL_LINE_STIPPLE);
    glPointSize( 10.0 );
    //glLineStipple(1, 0xFF00);
}

void points_and_linears()
{
  
    GLint i,j,c1,c2;
    glBegin(GL_POINTS);
    for(i=10;i<winWidth;i+=20)
      for(j=10;j<winHeight;j+=20)
      {
	POINT2D p=initPoint2D(i,j);
	if(dist_point_to_line(up,down,p)<0)
	  c1=0;
	else
	  c1=1;
	if(dist_point_to_line(left,right,p)<0)
	  c2=0;
	else
	  c2=1;
	glColor3f(c1,c2,0);
    glVertex2d(i,j);
      }
      glEnd();
      
    glColor3f( 0.0, 1.0, 0.0 );
    glLineWidth( 5.0 );
    glBegin( GL_LINES );
            glVertex2f( up.x,up.y ); //felső
	    glVertex2f( down.x,down.y ); //alsó
	    glVertex2f( right.x,right.y ); //jobb
	    glVertex2f( left.x,left.y ); //bal
    glEnd( );
    
    glColor3f( 1.0, 0.0, 0.0 );
    
    glBegin( GL_LINES );
	    glVertex2f( right.x,right.y ); //jobb
	    glVertex2f( left.x,left.y ); //bal
    glEnd( ); 
}

void keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = 1;
    if(keyStates[32])
    {
	    if(Move==0)
	    {
	      Move=elozo;
	      elozo=0;
	    }
	    else
	    {
	      elozo=Move;
	      Move=0;
	    }
    }
}

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void display( ) {
  
    glClear( GL_COLOR_BUFFER_BIT ) ;
    points_and_linears();
    GLint i;
    for(i=0;i<circle_count;i++)
    {
     circle(circle_points[i],CIRCLE_R);
     polygon(circle_points[i],CIRCLE_R,sides[i]);
    }
    glutSwapBuffers( );
}

void keyboard() {
    if(keyStates[27])
      circle_count=0;
    if(keyStates['a'] && down.x<winWidth)
	  {
            up.x-=2.5;
	    down.x+=2.5;
	  }
    if(keyStates['d'] && up.x<winWidth)
	  {
            up.x+=2.5;
	    down.x-=2.5;
	  }
    if(keyStates['w'] && right.y<winHeight)
	  {
            left.y-=2.5;
	    right.y+=2.5;
	  }
    if(keyStates['s'] && left.y<winHeight)
	  {
            left.y+=2.5;
	    right.y-=2.5;
	  }
    if(keyStates['W'])
	  {
            Move+=0.2;
	  }
    if(keyStates['S'])
	  {
            Move-=0.2;
	  }
    
  /*switch( key ) {
        case 27:
            circle_count=0;
            break;
        case 'a':
	  if(down.x<winWidth)
	  {
            up.x-=2.5;
	    down.x+=2.5;
	  }
            break;
        case 'd':
	  if(up.x<winWidth)
	  {
            up.x+=2.5;
	    down.x-=2.5;
	  }
            break;
	  case 'w':
	    if(right.y<winHeight)
	     {
		left.y-=2.5;
		right.y+=2.5;
	     }
          break;
	  case 's':
	    if(left.y<winHeight)
	      {
		left.y+=2.5;
		right.y-=2.5;
	      }
          break;  
	case 'W':
	  Move+=0.2;
	  break;
	 case 'S':
	  Move-=0.2;
	  break;
	  case 32:
	    if(Move==0)
	    {
	      Move=elozo;
	      elozo=0;
	    }
	    else
	    {
	      elozo=Move;
	      Move=0;
	    }
	 break;
    }*/
}

void processMouse( GLint button, GLint action, GLint xMouse , GLint yMouse ) {
  if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && circle_count<20 )
  {
    //GLdouble d=((rand()%10)+1)*pow(-1,rand()%2)/10.0;
    sides[circle_count]=rand()%8+3;
    circle_points[circle_count]=initPoint2D(xMouse,winHeight-yMouse);
    VECTOR[circle_count++]=initPoint2D(((rand()%10)+1)*pow(-1,rand()%2)/10.0,((rand()%10)+1)*pow(-1,rand()%2)/10.0);
    //VECTOR[circle_count++]=initPoint2D(1,1);
  }
  else if ( button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN  )
  {
    GLint i;
    for(i=0;i<circle_count;i++) //megkeressük a kört
    {
      glPointSize( 10.0 );
      POINT2D P=initPoint2D(xMouse,winHeight-yMouse);
      glBegin(GL_POINTS);
      glVertex2d(P.x,P.y);
      glEnd();
      if(dist2(circle_points[i],P)<CIRCLE_R*CIRCLE_R)
	break;
    }
    if(i!=circle_count) //ha van ilyen,akkor felülírjuk az utsóval és töröljük az utsót
    {
      VECTOR[i]=VECTOR[circle_count-1];
      sides[i]=sides[circle_count-1];
      circle_points[i]=circle_points[circle_count---1];
    }
  }
}

void update( int n )
{
    keyboard();
  for(GLint i=0;i<circle_count;i++)
  {
    //POINT2D tmp=initPoint2D(circle_points[i].x+VECTOR[i].x*Move,circle_points[i].y+VECTOR[i].y*Move); //a kövi pontja
   //if( tmp.x - CIRCLE_R < 0 || tmp.x + CIRCLE_R > winWidth)
    if( circle_points[i].x - CIRCLE_R < 0 || circle_points[i].x + CIRCLE_R > winWidth)
   {
     VECTOR[i].x*=-1;
     //tmp.x+=2*VECTOR[i].x;
   }
   //else if(tmp.y-CIRCLE_R<0 || tmp.y+CIRCLE_R > winHeight)
   else if(circle_points[i].y-CIRCLE_R<0 || circle_points[i].y + CIRCLE_R > winHeight)
   {
     VECTOR[i].y*=-1;
     //tmp.y+=2*VECTOR[i].y;
   }
   if(fabs(dist_point_to_line(up,down,circle_points[i]))<CIRCLE_R)
   {
     VECTOR[i]=mirroring(VECTOR[i],initPoint2D(up.x-down.x,up.y-down.y));
     //tmp=initPoint2D(circle_points[i].x+VECTOR[i].x*Move,circle_points[i].y+VECTOR[i].y*Move);
    }
   else if(fabs(dist_point_to_line(left,right,circle_points[i]))<CIRCLE_R)
   {
      VECTOR[i]=mirroring(VECTOR[i],initPoint2D(left.x-right.x,left.y-right.y));
      //tmp=initPoint2D(circle_points[i].x+VECTOR[i].x*Move,circle_points[i].y+VECTOR[i].y*Move);
   }
    circle_points[i].x+=VECTOR[i].x*Move;
    circle_points[i].y+=VECTOR[i].y*Move;
    //circle_points[i]=tmp;
  }
   glutPostRedisplay( );
   glutTimerFunc( 1, update, n );

}


int main( int argc, char** argv ) {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( winWidth, winHeight );
    glutInitWindowPosition( 100,100 );
    glutCreateWindow( "Ultimatetest" );
    srand(time(NULL));
    init( );
    glutDisplayFunc( display );
    glutKeyboardFunc( keyPressed );
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc( processMouse );
    
    glutTimerFunc( 1, update, 5 );
    
    glutMainLoop( );
    return 0;
}


