
#include "myglwidget.h"
#include <GL/gl.h>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);        // 🔥 activa el Z-buffer
    glDepthFunc(GL_LESS);           // (opcional, pero recomendable)

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

static void tri(float x1, float y1,float x2, float y2,float x3, float y3)
{
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
}

static void rectangulo(float x1, float y1,float x2, float y2)
{
    // Triángulo 1
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);

    // Triángulo 2
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
}

void MyGLWidget::paintGL()
{
    //Cielo
 glClearColor(0.55f,0.75f,0.95f,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
/*
    //Triangulo 1
    glVertex2f(0.f, 0.5f);
    glColor3f(1.f,0.f,0.f);

    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.f,1.0f,0.f);

    glVertex2f(0.5f, -0.5f);
    glColor3f(0.f,0.f,1.f);

    //Triangulo 2
    glVertex2f(0.f*2, 0.5f*2);
    glColor3f(1.f,0.f,0.f);

    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.f,1.0f,0.f);

    glVertex2f(0.5f, -0.5f);
    glColor3f(0.f,0.f,1.f);


    glVertex2f(0.02f, 0.02f);
    glColor3f(1.f,0.f,0.f);

    glVertex2f(-0.02f, -0.02f);
    glColor3f(0.f,1.0f,0.f);

    glVertex2f(0.02f, -0.02f);
    glColor3f(0.f,0.f,1.f);
 */

    //Suelo
    glColor3f(0.1f,0.45f,0.5f);
    rectangulo(-1,-1,1,-0.5);


    float x = -0.8f;
/*
    for (int i = 0; i < 1000; i++) {

        glColor3f(0.5f, 0.2f, 0.2f);

        //Parte Izquierda
        glVertex2f(x, -0.5f);
        glVertex2f(x +x+ 0.2f, -0.5f);
        glVertex2f(x + 0.1f, -0.2f);

        //Parte Derecha
        glVertex2f(x , 0.5f);
        glVertex2f(x + x, 0.5f);
        glVertex2f(x + x, 0.2f);

        x += 0.2f;
    }

*/
    glColor3f(0.2f,0.35f,0.25f);
    tri(-1.f,-0.6f,-0.5f,-0.55f,-0.75f,-0.2f);

    glColor3f(1,0.9,0.2);
    float cx = 0.7f;
    float cy = 0.7f;
    float s = 0.1f;

    tri(cx,cy,cx+s,cy,cx,cy+s);
    tri(cx,cy,cx-s,cy,cx,cy+s);
    tri(cx,cy,cx+s,cy,cx,cy-s);
    tri(cx,cy,cx-s,cy,cx,cy-s);


    glColor3f(0.2,0.5,0.9);
    int numMontanyas = 15;
    float step = 2.0f / numMontanyas;
    x = -1.0f;

    for(int i = 0; i < numMontanyas; i++)
    {
        float height = 0.2f + 0.05f * (i%2);
        tri(x,-0.6f,x + step, -0.6f, x + step/2,-0.6f + height);
        x+= step;
    }


    /*
    for(int i = 0; i < 6; i++)
    {
        float width = 0.35f;
        float height = 0.18f + 0.05f * (i%2);
        tri(x , -0.55f, x + width, 0.55,x+ width/2,-0.55 + height);
        x += width;
    }
    */



    glEnd();


}
