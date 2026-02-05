
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


void MyGLWidget::paintGL()
{

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
    */



    float x = -0.8f;

    for (int i = 0; i < 1000; i++) {

        glColor3f(1.0f, 0.5f, 0.2f);

        //Parte Izquierda
        glVertex2f(x, -0.5f);
        glVertex2f(x + 0.2f, -0.5f);
        glVertex2f(x + 0.1f, -0.2f);

        //Parte Derecha
        glVertex2f(x + 0.2f, -0.5f);
        glVertex2f(x + 0.2f, -0.5f);
        glVertex2f(x + 0.1f, -0.2f);

        x += 0.2f;
    }




    glEnd();


}
