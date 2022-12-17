#include<GL/glut.h>
#include<cstdio>
#include<cstring>
using namespace std;
struct Bar //Generic Bar value
{
float x;
float y;
float w;
float h;
float step;
};
struct Ball //Generic Ball Value
{
float r;
float x;
float y;
float velocity;
float xstep;
float ystep;
};
Bar bar = { 0, -11, 3, 1, 1.5}; //bar controlled by user
Bar top_bar = { 0, 11, 3, 1, 1.5 }; //top bar controlled by user
Ball ball = { 0.5, 0, 0, 0.2, 0.10, 0.10 }; //main ball
const float bar_maxr = 13;
const float bar_maxl = -13;
const float ball_maxu = 9.5;
const float ball_maxd = -9.5;
const float ball_maxr = 16;
const float ball_maxl = -16;
bool isReachedXMax = false;
bool isReachedYMax = false;
bool isGameEnd = false;
bool isGameOver = false;
const int zoom = -30;
static int player_score = 0;
static int cpu_score = -1;
static int player_lives = 3;
char finaltext[200];
static void printscore() //text to be displayed on the main screen
{
char text[100];
char text0[100];
char text1[100];
char text2[100];

sprintf(text," -------------PING-PONG------------");
glColor3f(0.6, 0.1, 0.2);
glRasterPos3f(-15, 7.00, zoom);
for (int i = 0; text[i] != '\0'; i++)
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text[i]);

sprintf(text0,"CPU_Score: %d ", cpu_score);
glColor3f(0.6, 0.5, 0.8);
glRasterPos3f(-15, 2, zoom);
for (int i = 0; text0[i] != '\0'; i++)

glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text0[i]);
sprintf(text1,"PLAYER_Score: %d PLAYER Lives: %d ",player_score,player_lives);
glColor3f(0.6, 0.5, 0.8);
glRasterPos3f(-15,-2, zoom);
for (int i = 0; text1[i] != '\0'; i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
sprintf(text2,"--------------------------------------------------------------");
glColor3f(0.8,1,0.7);
glRasterPos3f(-16, 0, zoom);
for (int i = 0; text2[i] != '\0'; i++)
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,text2[i]);
}
static void finalscreen() // output screen function
{
if (player_score == 10)
{
glColor3f(0.4, 0.8, 0.5);
}
else if (isGameOver)
{
glColor3f(0, 0, 0);
}

glRasterPos3f (-10, 0, zoom);
for (int i = 0; finaltext[i] != '\0'; i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, finaltext[i]);
glutSwapBuffers();
}
void render(void) // to display bar, top-bar and ball and required text on the screen
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
if (isGameEnd)
{
finalscreen();
return ;
}
printscore();
glPushMatrix();
glTranslatef(ball.x, ball.y, zoom);
glColor3f(0.1, 0.5, 0.8);
glutSolidSphere(ball.r, 20, 20);
glPopMatrix();
glPushMatrix();
glTranslatef(bar.x, bar.y, zoom);
glBegin(GL_QUADS);
glColor3f(1, 1, 1);
glVertex2f(bar.w, bar.h);
glColor3f(1, 1, 0);
glVertex2f(bar.w, -bar.h);
glColor3f(0, 0, 0);
glVertex2f(-bar.w, -bar.h);
glColor3f(1, 1, 0);
glVertex2f(-bar.w, bar.h);
glColor3f(1, 1, 1);
glEnd();
glPopMatrix();
glPushMatrix();
glTranslatef(top_bar.x, top_bar.y, zoom);
glBegin(GL_QUADS);
glColor3f(0.5, 0, 0.5);
glVertex2f(top_bar.w, top_bar.h);
glColor3f(1, 0, 1);
glVertex2f(top_bar.w, -top_bar.h);
glColor3f(1, 1, 1);
glVertex2f(-top_bar.w, -top_bar.h);
glColor3f(1, 1, 1);
glVertex2f(-top_bar.w, top_bar.h);
glEnd();
glPopMatrix();
glutSwapBuffers();
}
void init(void) //initialize the required in-built functions
{
glClearColor(0.0,0.0,0.0,0.0);
glClearDepth(1.0);
glEnable(GL_DEPTH_TEST);
glShadeModel(GL_SMOOTH);
glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) //reshape of window

{
float aspectRatio;
h = (h == 0) ? 1 : h;
w = (w == 0) ? 1 : w;
glViewport(0, 0, w, h);
aspectRatio = (float)w / (float)h;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45, aspectRatio, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);
}
void idle() //the ball movement across the bar and counting the score
{
if (ball.y <= ball_maxd)
{
if (ball.x <= bar.x - bar.w | ball.x >= bar.x + bar.w)
{
player_lives--;
bar.x = ball.x;
bar.y = -11;
if (player_lives == 0)
{
glClearColor(1, 0, 0, 1);
isGameEnd = true;
isGameOver = true;
strcpy(finaltext, "Game Over!! You lost all three balls.CPU Won");
}
}
else
{
player_score++;
ball.velocity += 0.12;
}
}
if (ball.y <= ball_maxu)

{
if(ball.x <= top_bar.x - top_bar.w | ball.x >= top_bar.x + top_bar.w)
{
top_bar.x = ball.x;
top_bar.y = +11;
}

}
else{cpu_score++;}
if (isGameEnd)
return;
if(player_score == 10)
{
glClearColor(0.8,0.5,0.4,1);
strcpy(finaltext, " Player 1 Won");
isGameEnd = true;
}
else if(cpu_score==10)
{
glClearColor(0.8,0.5,0.4,1);
strcpy(finaltext, " CPU Won");
isGameEnd = true;
}
if (ball.x > ball_maxr)
{
glColor3f(1.0, 0.0, 1.0);
isReachedXMax = true;
}
else if (ball.x<ball_maxl)
{
glColor3f(1.0, 0.8, 1.0);
isReachedXMax = false;
}
if (ball.y>ball_maxu)
{
glColor3f(1.0, 0.8, 0.1);
isReachedYMax = true;
}
else if (ball.y < ball_maxd)
{
glColor3f(0.5, 0.8, 0.1);
isReachedYMax = false;
}
if (isReachedXMax)
ball.x -= ball.xstep * ball.velocity;
else
ball.x += ball.xstep * ball.velocity;
if (isReachedYMax)
ball.y -= ball.ystep * ball.velocity;
else
ball.y += ball.ystep * ball.velocity;
glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) // keyboard function for display()
{
switch (key)
{
case 27: exit(1);
}
}
void specialkey(int key, int x, int y) //additional key config for display()
{
if (key == GLUT_KEY_LEFT && bar.x > bar_maxl)
{
bar.x -= bar.step;
}
else if (key == GLUT_KEY_RIGHT && bar.x < bar_maxr)
{
bar.x += bar.step;
}
}
void display() //main screen function
{
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(640, 480);
glutCreateWindow("Ping Pong Game");
init();
glutReshapeFunc(reshape);
glutDisplayFunc(render);
glutKeyboardFunc(keyboard);
glutSpecialFunc(specialkey);
glutIdleFunc(idle);
}
int flag=0;
void drawstring(int x,int y,char *string)
{
int len = (int) strlen(string);
int i;
glRasterPos2f(x,y);
for(i = 0;i<len;i++)
{
glColor3f(0.0,0.0,0.0);
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
}
}
 void frontscreen() //start screen text display
 {
 glClear(GL_COLOR_BUFFER_BIT);

 glColor3f(1,0.1,1);
 drawstring(-20,-65,"<<<<<<<PRESS ENTER TO START>>>>>>>>");
 glFlush();
 }
void mydisplay(void) //decides to stay in start screen or move to main screen
{
glClear(GL_COLOR_BUFFER_BIT);
if(flag==0)
frontscreen ();
if(flag==1)
display();
}

void myKeyboardFunc(unsigned char key,int x,int y) //keyboard function for start screen
{
switch(key)
{
case 13:if(flag==0)

flag=1;
break;
}
mydisplay();
}

void init1(void) //init function for front screen
{
glClearColor(1.0,0.9,0.7,0);
glOrtho(-100.0,100.0,-100.0,100.0,-50.0,50.0);
}

int main(int argc, char** argv) //front screen function
{
glutInit(&argc, argv);
glutInitWindowSize(1000, 480);
glutCreateWindow("Start-Screen");
init1();
glutDisplayFunc(frontscreen);
glutKeyboardFunc(myKeyboardFunc);
glutMainLoop();
return 0;
}

