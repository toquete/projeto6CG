/*********************************************************************
 * Projeto 6 - CG - Curvas de Bézier
 *
 * César Yugo Okada e Guilherme Toquete
 *
 * Algoritmo que gera uma curva de Bézier com 4 pontos fixos.
 *
 *              COMANDOS
 * Botão direito do mouse descola o ponto de controle direito
 * Botão esquerdo do mouse desloca o ponto de controle esquerdo
 *
 * ********************************************************************/

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define HEIGHT 500
#define WIDTH 500


float points[4][2];
int idx;

void init()
{

   points[0][0] = -1.0;
   points[0][1] =  0.0;

   points[1][0] = -0.5;
   points[1][1] = -0.5;

   points[2][0] =  0.5;
   points[2][1] =  0.5;

   points[3][0] =  1.0;
   points[3][1] =  0.0;
}

void atualizaPoints(int x, int y)
{
   float cx, cy;

   cx = ((float)(2 * x) / (float)WIDTH) - 1;
   cy = ((float)(2 * y) / (float)HEIGHT) - 1;
   cy *= -1;

   points[idx][0] = cx;
   points[idx][1] = cy;
   glutPostRedisplay();
}


//função detecta os eventos do mouse
void keyBoard(int botao, int estado, int x, int y)
{
   if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN))
      idx = 1;

   if ((botao == GLUT_RIGHT_BUTTON) && (estado == GLUT_DOWN))
      idx = 2;

   atualizaPoints(x, y);
}

void callBack(int x, int y)
{
   atualizaPoints(x, y);
}

float fatorial(int a)
{
   int i;
   float result;

   result = 1.0;
   for (i = a; i > 0; i--)
      result *= (float) i;
   return result;
}

/*
 * float combinacao(int a, int b) e float fatorial(int a)
 * efetua o calculo da combinação para a função polinomial de Berntein
 */

float combinacao(int a, int b)
{
   return fatorial(b) / (fatorial(a) * fatorial(b - a));
}


void display()
{
   int i;
   float u,x,y;

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINE_STRIP);
   for (i = 0; i < 4; i++)
      glVertex2f(points[i][0], points[i][1]);
   glEnd();

   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_POINTS);
   for (u = 0.0; u <= 1.0;u += 0.001)
   {
      x = 0.0;
      y = 0.0;
      for (i = 0; i < 4; i++)
      {
         x += combinacao(i, 3) * pow(u, i) * pow(1.0f - u, 3 - i) * points[i][0];
         y += combinacao(i, 3) * pow(u, i) * pow(1.0f - u, 3 - i) * points[i][1];
      }
      glVertex2f(x, y);
   }
   glEnd();

   glFlush();
}

void inicializaOpenGL()
{
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Define o modo inicial de apresentação
   glutInitWindowPosition(500,100); // Define a posição inicial da tela a ser apresentada
   glutInitWindowSize(WIDTH, HEIGHT); // Define o tamanho da tela a ser apresentada
   glutCreateWindow("Curva de Bézier");
   glClearColor(1.0,1.0,1.0,0);// define a cor de fundo da janela (no caso, branco)
   glPointSize(2.0);
}


int main(int argc, char** argv)
{
   init();
   glutInit(&argc,argv);
   inicializaOpenGL();
   glutDisplayFunc(display); //pinta os pontos
   glutMouseFunc(keyBoard); //captura os eventos do mouse
   glutMotionFunc(callBack); //atualiza a janela de desenho
   glutMainLoop();

   return 0;
}

