#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void ResizeWindow(GLFWwindow* window,int iFrameBufferWidth,int iFrameBufferHeight) {
    glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}


int main(void)
{
    int iFrameBufferWidth = 0;
    int iFrameBufferHeight = 0;
    //GLFWwindow* window;

    /* Initialize the library */
        //INICIAMOS GLEW Y CONTROLAMOS ERRORES
    if (!glfwInit()) {
        return -1;
    }


    //Crear el contexto para utilizar las ventanas en opengl
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,);

   
    //inicializar la ventana
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"mi ventana",NULL,NULL);

    //definir ese buffer
    glfwGetFramebufferSize(window, &iFrameBufferWidth, &iFrameBufferHeight);

    //DEFINIMOS TAMAÑO VIEWPORT
    glViewport(0,0, iFrameBufferWidth, iFrameBufferHeight);


    //definimos que ventana usar
    glfwMakeContextCurrent(window);

    //permitir que GLEW utilice funciones modernas de opengl
    glewExperimental = GL_TRUE;


    if (glewInit() != GLEW_OK) {
        // Error al inicializar GLEW
        return -1;
    }

    glClearColor(1.f, 0.f, 0.f, 1.f);

    GLuint vaoPuntos, vboPuntos;
    
    //Definimos cuantas ordenes vamos a guardar(cantidad VAO)

    glGenVertexArrays(1, &vaoPuntos);
    //definir que vao esta activo
    glBindVertexArray(vaoPuntos);

    //definimos vbo a crear y donde lo almacenamos
    glGenBuffers(1, &vboPuntos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);


    // Permitir cambiar tamaño del punto desde shader
    glEnable(GL_PROGRAM_POINT_SIZE);

    // =========================
    // SHADERS
    // =========================

    const char* vertexShaderSource =
        "#version 440 core\n"
        "layout (location = 0) in vec2 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(position, 0.0, 1.0);\n"
        "   gl_PointSize = 20.0;\n"
        "}\n";

    const char* fragmentShaderSource =
        "#version 440 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Error vertex shader: %s\n", infoLog);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
 

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Error vertex shader: %s\n", infoLog);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    GLfloat punto[] = { 0.0f,0.0f, 0.5f,  0.5f };

    //damos ordenes
    glBufferData(GL_ARRAY_BUFFER, sizeof(punto), punto, GL_STATIC_DRAW);

    //**** indicamos donde almacenar y distribuir la informacion

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    //indicar que la grafica pueda usar el atributo 0

    glEnableVertexAttribArray(0);

    //cerramos o "desvincular" vao y vbo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        //pulleamos los events del input
        glfwPollEvents();

        float time = glfwGetTime();
        float green = sin(time);
        


        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);


        //Dibujar y mostrar
        glUseProgram(shaderProgram);
        glBindVertexArray(vaoPuntos);
        glDrawArrays(GL_POINTS,0,2);

        //Dejamos de usar el vao
        glBindVertexArray(0);


        glFlush();
        glfwSwapBuffers(window);
    }



    glfwTerminate();
    return 0;

}



