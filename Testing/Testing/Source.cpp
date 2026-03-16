#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void ResizeWindow(GLFWwindow* window, int iNewFrameBufferWidth, int iNewFrameBufferHeight)//Te da los puxeles del viewport
{//Definir tamaño del viewoport
	glViewport(0, 0, iNewFrameBufferWidth, iNewFrameBufferHeight);
}


void main()
{

	//Inicializo GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuro drivers y version de OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Usa las funciones segun que grafica se esta usando

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);//Usa los drivers 4.4 de la tarjeta grafica
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Richard", NULL, NULL); //glfwGetPrimaryMonitor() para hacerlo full screen en le primer null

	//Obtenemos tamaño del buffer (viewport)
	//Obetenemos callback para el resize de la ventana
	glfwSetFramebufferSizeCallback(window, ResizeWindow);

	

	//Definir ventana en la que trabajare
	glfwMakeContextCurrent(window);

	//Activo funciones experimentales para todas las graficas (sobretodo las antiguas)
	glewExperimental = GL_TRUE;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "Ha funcionado" << std::endl;
		glClearColor(1.f, 0.f, 0.f, 1.f);

		GLuint vaoPuntos, vboPuntos;
		//Genero 1 VAO y almaceno la referencia en vaoPuntos
		glGenVertexArrays(1, &vaoPuntos);

		//Activo VaoPuntos
		glBindVertexArray(vaoPuntos);

		//Genero 1 VBO y almaceno la referencia en vboPuntos
		glGenBuffers(1, &vboPuntos);

		//Indico que VBO es el activo y que este almacena array de datos
		glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);

		//Declaro puntos {x,y}
		GLfloat punto[] = { 0.f,0.f };
		
		//Vuelco el array en el VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(punto), punto, GL_STATIC_DRAW);

		//Indico como leer la informacion
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

		//Activo los datos para que la GPU pueda usarlos
		glEnableVertexAttribArray(0);

		//Desvinculo VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Desvinculo VAO
		glBindVertexArray(0);


		while (!glfwWindowShouldClose(window))
		{
			//Pulleamos eventos
			glfwPollEvents();

			//Limpiar Buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


			//Activo VAO con la geometria cargada
			glBindVertexArray(vaoPuntos);

			//Dibujo geometria cargada
			glDrawArrays(GL_POINTS,0,1);

			//Desvinculo VAO
			glBindVertexArray(0);

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);


		}
	}
	else
	{
		std::cout << "Hizo pum" << std::endl;
		glfwTerminate();
	}

	glfwTerminate();



}



