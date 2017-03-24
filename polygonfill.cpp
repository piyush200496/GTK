#include<GL/gl.h>
#include<GL/freeglut.h>
#include<stdio.h>
int m,s1,s2,s3,wid;
void maininit()
{
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,360,0,270);
}
void s1init()
{
    glClearColor(0.3,0.4,0.5,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0,120,0,270);
}
void s2init()
{
    glClearColor(0.5,0.4,0.5,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0,120,0,270);
}
void d(){}
void s3init()
{
    glClearColor(0.3,0.2,0.3,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0,120,0,270);
}
void s1display(){ //flood fill
glRasterPos2f(10,200 );
  glColor3f(0.4, 0.7, 0.7);
  glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)"Piyush Mishra");
  glRasterPos2f(10, 180);
  glColor3f(0.4, 0.7, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"Roll No-45(B1)");
  glRasterPos2f(10, 160);
  glColor3f(0.4, 0.7, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"CSE-CCVT(6th sem)");
  glRasterPos2f(10, 140);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"flood fill");
  glRasterPos2f(10, 130);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"multicolour boundary");
glColor3ub(100,100,100);
glBegin(GL_POLYGON);
glVertex2i(30,50);
glVertex2i(90,50);
glVertex2i(90,100);
glVertex2i(30,100);
glEnd();
glBegin(GL_LINE_LOOP);
	glColor3ub(220,135,121);
	glVertex2i(30,50);
	glColor3ub(250,85,211);
	glVertex2i(90,50);
	glColor3ub(140,155,211);
	glVertex2i(90,100);
	glColor3ub(150,125,132);
	glVertex2i(30,100);
	glEnd();
	glFlush();
}
void s2display(){ //flood fill
    glRasterPos2f(10, 180);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"flood fill single color");
  glRasterPos2f(10, 170);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"boundary");
glColor3ub(200,200,100);
glBegin(GL_POLYGON);
glVertex2i(30,50);
glVertex2i(90,50);
glVertex2i(90,100);
glVertex2i(30,100);
glEnd();
glColor3ub(200,190,180);
glBegin(GL_LINE_LOOP);
glVertex2i(30,50);
glVertex2i(90,50);
glVertex2i(90,100);
glVertex2i(30,100);
glEnd();
glFlush();
}
void s3display(){ //boundary fill
    glRasterPos2f(10, 180);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"boundary fill multi");
  glRasterPos2f(10, 170);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"color boundary");
/*glColor3ub(100,100,100);
glBegin(GL_POLYGON);
glVertex2i(30,50);
//glColor3ub(200,190,180);
glVertex2i(50,70);
//glColor3ub(200,190,180);
glVertex2i(60,50);
//glColor3ub(200,190,180);
glVertex2i(80,70);
//glColor3ub(200,200,100);
glVertex2i(90,50);
//glColor3ub(200,200,100);
glVertex2i(80,30);
//glColor3ub(200,190,180);
glVertex2i(60,50);
//glColor3ub(200,190,180);
glVertex2i(50,30);
//glColor3ub(200,190,180);
glEnd();
*/
glColor3ub(200,190,180);
glBegin(GL_LINE_LOOP);
glVertex2i(30,50);
glColor3ub(200,190,180);
glVertex2i(50,70);
glColor3ub(200,190,180);
glVertex2i(60,50);
glColor3ub(200,190,180);
glVertex2i(80,70);
glColor3ub(255,0,0);
glVertex2i(90,50);
glColor3ub(255,0,0);
glVertex2i(80,30);
glColor3ub(200,190,180);
glVertex2i(60,40);
glColor3ub(200,190,180);
glVertex2i(50,30);
glColor3ub(200,190,180);
glVertex2i(30,50);
glEnd();
glFlush();
}
void floodfill(int x,int y,unsigned char fillcolor[],unsigned char oldcolor[])
 {  //IF FILL COLOR IS SAME AS OLD COLOR< DON"T DO ANYTHING
	if(oldcolor[0]==fillcolor[0] && oldcolor[1]==fillcolor[1] && oldcolor[2]==fillcolor[2])
	 	return;
    unsigned char color[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,color);
    //IF OBTANED PIXEL DOES NOT BELONG TO INTERIOR OF POLYGON
    if(oldcolor[0]!=color[0] && oldcolor[1]!=color[1] && oldcolor[2]!=color[2])
	 {return;}
	glColor3ubv(fillcolor);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	printf("x=%d,y=%d\n",x,y);
	glEnd();
	glFlush();
    floodfill(x+1,y,fillcolor,oldcolor);
    floodfill(x,y+1,fillcolor,oldcolor);
    floodfill(x-1,y,fillcolor,oldcolor);
    floodfill(x,y-1,fillcolor,oldcolor);
}

void boundaryfill(int x,int y,unsigned char fillcolor[],unsigned char boundarycolor[])
{
    unsigned char color[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,color);
    //IF OBTAINED PIXEL LIES ON POLYGON BOUNDRAY
   if((boundarycolor[0]==color[0] && boundarycolor[1]==color[1] && boundarycolor[2]==color[2]))
	 {return;}
	 //IF OBTAINED PIXEL IS ALREADY OF SAME COLOR AS FILL COLOR
	if(color[0]==fillcolor[0] && color[1]==fillcolor[1] && fillcolor[2]==color[2])
		return;
	glColor3ubv(fillcolor);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	printf("x=%d,y=%d\n",x,y);
	glEnd();
	glFlush();
    boundaryfill(x+1,y,fillcolor,boundarycolor);
    boundaryfill(x-1,y,fillcolor,boundarycolor);
    boundaryfill(x,y+1,fillcolor,boundarycolor);
    boundaryfill(x,y-1,fillcolor,boundarycolor);
}
void mouse(int button,int state,int x,int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int wid=glutGetWindow();
		if(wid==s1)
		{
			y=(270-y);
			unsigned char fillcolor[3]={255,254,0};
			unsigned char oldcolor[3]={100,100,100};
			floodfill(x,y,fillcolor,oldcolor);
			printf("flood fill multicolor boundary\n");
		}
		else if(wid==s2)
		{
	    	y=(270-y);
			unsigned char fillcolor[3]={255,254,0};
			unsigned char oldcolor[3]={200,200,100};
			floodfill(x,y,fillcolor,oldcolor);
			printf("flood fill single color boundary\n");
		}
		else if(wid==s3)
        {
         y=(270-y);
			unsigned char fillcolor[3]={255,254,0};
			unsigned char boundarycolor[3]={200,190,180};
			boundaryfill(x,y,fillcolor,boundarycolor);
			printf("boundary fill single color boundary\n");
        }
	}
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(360,270);
    glutInitWindowPosition(100,100);
    m=glutCreateWindow("filling algorithms- Piyush");
    maininit();
    glutDisplayFunc(d);
    //l,b,r,t
    s1=glutCreateSubWindow(m,0,0,120,270);
    s1init();
    glutDisplayFunc(s1display);
    glutMouseFunc(mouse);
    s2=glutCreateSubWindow(m,120,0,120,270);
    s2init();
    glutDisplayFunc(s2display);
    glutMouseFunc(mouse);
    s3=glutCreateSubWindow(m,240,0,120,270);
   s3init();
    glutDisplayFunc(s3display);
   glutMouseFunc(mouse);
    glutMainLoop();
}
