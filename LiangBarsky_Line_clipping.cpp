#include<GL/gl.h>
#include<stdio.h>
#include<GL/freeglut.h>
float p[4], q[4], t1,t2;
bool b1=false,b2=false;
int lb=0,rb=0;
int xmin=100,xmax=700,ymin=100,ymax=700;
int x1,y1,x2,y2;
void initgl()
{
    glClearColor(0.0,0.0,0.0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,900,0,900);
}
void display();
void liang(int xi,int yi, int xf, int yf);
void draw(int xx1,int yy1,int xx2,int yy2);
void draw(int xx1,int yy1,int xx2,int yy2)
{
    glColor3ub(255,0,0);
    glBegin(GL_LINES);
    glVertex2i(xx1,yy1);
    glVertex2i(xx2,yy2);
    glEnd();
  /*  if(b1){
     b1=false;
     x1=0;y1=0;
    }
     if(b2){
        b2=false;
        x2=0;y2=0;
     }
    */
   glFlush();

}
void liang(int xi, int yi, int xf, int yf)
{int tx1,tx2,ty1,ty2,i;
 lb=0; rb=0;
    int dx=xf-xi;
    int dy=yf-yi;
    float temp=0.0;
     p[0]=-dx;
    p[1]=dx;
    p[2]=-dy;
    p[3]=dy;

    q[0]=xi-xmin;
    q[1]=xmax-xi;
    q[2]=yi-ymin;
    q[3]=ymax-yi;
    for( i=0;i<4;i++)
    {
        if(p[i]==0)
        {
            printf("line parallel to boundary\n");
            if(q[i]>=0){
                    if(i<2)
                    {
                        if(yi<ymin)
                            yi=ymin;
                        if(yf>ymax)
                            yf=ymax;
                       if(yf<ymin)
                            yf=ymin;
                     if(yf>ymax)
                             yf=ymax;


                    }
                    if(i>1)
                    {
                        if(xi<xmin)
                            xi=xmin;
                         if(xf>xmax)
                            xf=xmax;
                        if(xf<xmin)
                            xf=xmin;
                        if(xf>xmax)
                            xf=xmax;

                    }
                draw(xi,yi,xf,yf);
            }
        }
    }
    t1=0;t2=1;
    for(i=0;i<4;i++)
    {temp=q[i]/p[i];
     if(p[i]<0)
     {
         if(t1<=temp)
            t1=temp;
     }
        else{if(t2>temp)
            t2=temp;
             }
    }
   if(t1<t2)
   {tx1=xi+t1*p[1];
    tx2=xi+t2*p[1];
    ty1=yi+t1*p[3];
    ty2=yi+t2*p[3];
    draw(tx1,ty1,tx2,ty2);
   }

}
void display()
{glRasterPos2f(200,880 );
  glColor3f(0.4, 0.7, 0.7);
  glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)"Piyush Mishra");
  glRasterPos2f(200, 860);
  glColor3f(0.4, 0.7, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"Roll No-45(B1)");
  glRasterPos2f(200, 840);
  glColor3f(0.4, 0.7, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"CSE-CCVT(6th sem)");
  glRasterPos2f(200, 810);
  glColor3f(0.4, 0.8, 0.7);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10,(const unsigned char*)"Liang Barsky Algorithm");


     glColor3ub(0,255,0);
 glBegin(GL_LINE_LOOP);
 glVertex2i(xmin,ymin);
 glVertex2i(xmax,ymin);
 glVertex2i(xmax,ymax);
 glVertex2i(xmin,ymax);
 glEnd();
glFlush();
}
void mouse(int button,int state,int x,int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x1=x;
        y1=900-y;
       lb++;
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        x2=x;
        y2=900-y;
      rb++;
    }
if(lb!=0 && rb!=0)
liang(x1,y1,x2,y2);
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(900,900);
    glutInitWindowPosition(0,0);
    glutCreateWindow("piyush");
    initgl();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
