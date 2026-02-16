
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

static void tri(float x1, float y1,float z1,
                float x2, float y2,float z2,
                float x3, float y3,float z3)
{
    glVertex3f(x1,y1,z1);
    glVertex3f(x2,y2,z2);
    glVertex3f(x3,y3,z3);
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


static void pine(float x, float y, float size,float sway)
{
    glColor3f(0.55f, 0.27f, 0.07f);

    float trunkWidth = size / 10.0f;
    float trunkHeight = size / 2.0f;

    // Triángulo del tronco 1 (Mitad inferior-derecha)
    glVertex2f(x - trunkWidth / 2, y);                  // Abajo Izq
    glVertex2f(x + trunkWidth / 2, y);                  // Abajo Der
    glVertex2f(x + trunkWidth / 2, y + trunkHeight);    // Arriba Der

    // Triángulo del tronco 2 (Mitad superior-izquierda)
    glVertex2f(x - trunkWidth / 2, y);                 // Abajo Izq
    glVertex2f(x + trunkWidth / 2, y + trunkHeight);   // Arriba Der
    glVertex2f(x - trunkWidth / 2, y + trunkHeight);   // Arriba Izq

    glColor3f(0.13f, 0.55f, 0.13f);

    float triangleBaseY = y + trunkHeight * 0.8f;
    float triangleHeight = size / 2.5f;
    float currentSize = size;

    /*
    for(int i = 0; i < 3; i++) {
        // Dibujamos un triángulo
        glVertex2f(x - currentSize / 2, triangleBaseY);        // Izquierda
        glVertex2f(x + currentSize / 2, triangleBaseY);        // Derecha
        glVertex2f(x, triangleBaseY + triangleHeight);
    }
*/
    float currentX = x;

    for(int i = 0; i < 3; i++) {

        // Cuanto mas alto ms fuerte es l viento
        float windEffect = sway * (1.0f + i * 0.5f);

        //rotacion triangulo
        float leftX = currentX - currentSize / 2 + (windEffect * 0.3f);
        float rightX = currentX + currentSize / 2 + (windEffect * 0.3f);

        float topX = currentX + windEffect;

        glVertex2f(leftX + (windEffect * 0.2f), triangleBaseY); // Izq
        glVertex2f(rightX + (windEffect * 0.2f), triangleBaseY); // Der
        glVertex2f(topX, triangleBaseY + triangleHeight);           // Punta (más movida)

        //  siguiente capa de pino
        triangleBaseY += triangleHeight * 0.5f;
        currentSize *= 0.8f;
    }


}

void MyGLWidget::paintGL()
{
    //Cielo
    glClearColor(0.55f,0.75f,0.95f,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    static float cam = 0.0f;
    float viento = sin(cam * 10.0f) * 0.05f;
    cam += 0.025f;

    //RAYO CLASE
    static int flash = 0;

    if (flash > 0){
        glClearColor(1.f, 1.f, 1.f, 1.f);
        flash--;
    } else {
        glClearColor(0.55f, 0.75f, 0.95f, 1.f);
    }

    // probabilidad del relámpago

    if ((std::rand() % 200) == 0) flash = 2;

    // limpia

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float dark = (flash > 0) ? 0.4f : 1.0f;

     glColor3f(0.1f*dark, 0.45f*dark, 0.12f*dark);


    glPushMatrix();

    glTranslatef(viento * 1.0,0.0f,0.0f);
    glBegin(GL_TRIANGLES);

    //glColor3f(1,0,0);
    //tri(-0.5f,0.5f,5.f,0.1f,.2f,3.f,1.f,0.5f,.2f);
     //glColor3f(1,1,0);
    //tri(0.1f,0.5f,.9f,0.1f,.3f,3.f,1.f,0.2f,.2f);



    //Suelo
    /*
    glColor3f(0.1f,0.45f,0.5f);
    rectangulo(-1,-1,1,-0.5);


    float x = -0.8f;

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
*/

    /*
    for(int i = 0; i < 6; i++)
    {
        float width = 0.35f;
        float height = 0.18f + 0.05f * (i%2);
        tri(x , -0.55f, x + width, 0.55,x+ width/2,-0.55 + height);
        x += width;
    }


    //glColor3f(0.2f,0.35f,0.25f);
    //tri(.2f,-0.6f,-0.5f,-0.55f,-0.75f,-0.2f);

    //rectangulo(-0.2f,-1.f,0.5f,0.2f);

 */
    int numMontanyas = 5;
    float step = 2.0f / numMontanyas;
    float x = -1.0f;



    for(int i = 0; i < numMontanyas; i++)
    {
        glColor3f(0.78, 0.376, 0);
        float vientoLocal = sin((cam * 5.0f) + i) * 0.2f;
        pine(x,-.9f,.5f,vientoLocal);
        x += step;
    }



    glEnd();

    glPopMatrix();
    update();
}
