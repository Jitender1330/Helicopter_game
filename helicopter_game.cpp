#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
float speed=0.15;
float block1x=50.0,block1y=0;//block 1
float copter=0.0;//copter moving
int i=0;
int score=0;
char scs[20];
int check=1;
int gameover=0;
int frontscreen=1;


void restart()
{
	speed=0.15;
	block1x=50.0,block1y=(rand()%45)+10;//block 1
	copter=0.0;//copter moving
	i=0;
	score=0;
	scs[20];
	check=1;
	gameover=0;
	frontscreen=1;
}

void init(void)
{
	block1y=(rand()%45)+10;
	glClearColor (0.4, 0.3, 0.7, 0.0);
	glShadeModel (GL_SMOOTH);
	glLoadIdentity ();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , 0.0);
}

void drawcopter()
{
	glColor3f(200.0/200.0,51.0/200.0,51.0/200.0);
	glRectf(13,49.8,17.8,44.8);//body
	glRectf(9,46,13,48);//tail
	glRectf(9,46,10,51);//tail up
	glRectf(15,49.8,15.8,52.2);//propeller stand
	glRectf(11,53.6,19.0,52.2);//propeller
	
}

void renderBitmapString(float x,float y,float z,void *font,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void output(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(frontscreen)
	{
		glColor3f(1.0,1.0,1.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(0.0,0.0,1.0);
		renderBitmapString(30,85,0,GLUT_BITMAP_TIMES_ROMAN_24,"MARATHA MANDAL ENGINEERING COLLEGE , BELAGAVI");
		renderBitmapString(35,75,0,GLUT_BITMAP_TIMES_ROMAN_24,"Department Of Computer Science Enginering");
		renderBitmapString(40,65,0,GLUT_BITMAP_TIMES_ROMAN_24,"Project on Helicopter game");
		renderBitmapString(35,50,0,GLUT_BITMAP_TIMES_ROMAN_24,"Under the Guidance of: 	Prof. Gautam Y Kamble");
		renderBitmapString(35,40,0,GLUT_BITMAP_TIMES_ROMAN_24,"Name: Jitender Dahiya" 	"\tUSN: 2MM17CS016");              
		renderBitmapString(10,30,0,GLUT_BITMAP_HELVETICA_18,"Instructions:");
		renderBitmapString(10,25,0,GLUT_BITMAP_HELVETICA_18,"Click and hold left mouse button to moveup");
		renderBitmapString(10,20,0,GLUT_BITMAP_HELVETICA_18,"Release the mouse click to move down");
		renderBitmapString(10,15,0,GLUT_BITMAP_HELVETICA_18,"Click to Play or Q to Quit and R to Restart");
		glutSwapBuffers();
		glFlush();
	}
							//Crash condition
	if((gameover || i==238||i==-238) //top and bottom checking
	||(((int)block1x==10||(int)block1x==7||(int)block1x==4||(int)block1x==1) &&(int)block1y<53+(int)copter&&(int)block1y+35>53+(int)copter)//propeller front checking
	||(((int)block1x==9||(int)block1x==3||(int)block1x==6)&&(int)block1y<45+(int)copter&&(int)block1y+35>45+(int)copter)//lower body checking
	||(((int)block1x==0)&&(int)block1y<46+(int)copter&&(int)block1y+35>46+(int)copter)//lower tail checking
	)
	{
		gameover = 1;
		glColor3f(1.0,1.0,1.0);
		glRectf(0.0,0.0,100.0,100.0);
		glColor3f(0.0,0.0,1.0);
		renderBitmapString(10,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER!!!");
		renderBitmapString(20,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"SCORE:");
		renderBitmapString(28,58,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		renderBitmapString(20,50,0,GLUT_BITMAP_TIMES_ROMAN_24,"Press Q to Quit, R to Restart");
		glutSwapBuffers();
		glFlush();
	}
	else if(check==0)
	{
		glPushMatrix();
		glColor3f(0.5,0.8,0.2);
		glRectf(0.0,0.0,100.0,10.0);//ceil
		glRectf(0.0,100.0,100.0,90.0);//floor
		sprintf(scs,"%d",score);
		glTranslatef(0.0,copter,0.0);
		drawcopter();//code for helicopter
		if(block1x<-10)
		{
			block1x=50;
			block1y=(rand()%25)+20;
			score+=50;
		}
	else {block1x-=speed;}
		glTranslatef(block1x,-copter,0.0);
		glColor3f(1.0,0.0,0.0);
		glRectf(block1x,block1y,block1x+5,block1y+35);//block 1
		glPopMatrix();
		renderBitmapString(20,95,0,GLUT_BITMAP_TIMES_ROMAN_24,"SCORE:");
		renderBitmapString(28,95,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
		glFlush();
		glutSwapBuffers();
	}
}

void Heliup()
{
	copter+=0.15;
	i+=1;
	glutPostRedisplay();
}

void Helidown()
{
	copter-=0.15;
	i-=1;
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		frontscreen=0;
		check=0;
		glutIdleFunc(Heliup);
	}

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	glutIdleFunc(Helidown);
	glutPostRedisplay();
}

void dummy(){}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 'q' || key == 'Q')
	{
	exit(0);
	}

	if(key == 'r' || key == 'R'){
	glutIdleFunc(dummy);
	restart();
}
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize (500, 400);
glutInitWindowPosition (200,300);
glutCreateWindow ("Helicopter game");
glutFullScreen();
init();
glutDisplayFunc(display);
glutMouseFunc(mouse);
glutKeyboardFunc(keyboard);
glutMainLoop();
}
