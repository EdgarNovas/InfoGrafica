#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //Crear el contexto para utilizar las ventanas en opengl
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

   
    //inicializar la ventana
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"mi ventana",NULL,NULL);

    return 0;
}