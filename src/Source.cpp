#include "glad/glad.h"
#include "glfw3.h"
#include "glad.c"

//math lib....
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "img.h"

float window_width = 980;
float window_height = 540;
const char * window_title = "3D";

float f = 0.0f;
float* fValue = &f;

float x = 0.0f;
float* xValue = &x;

float y = 0.0f;
float* yValue = &y;

	int main()
	{
		glfwInit();
		GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

		glfwWindowHint(GL_MAJOR_VERSION, 3);
		glfwWindowHint(GL_MINOR_VERSION, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int vSuccess;
		GLchar infolog[1000];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);
		glGetShaderInfoLog(vertexShader, 1000, 0, infolog);

		if (vSuccess)
		{
			std::cout << "Vertex Shader is okk" << std::endl;
		}
		else
		{
			std::cout << "Error in Vertex Shader: " << infolog;
		};

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		int fSuccess;
		GLchar infoLog[1000];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);
		glGetShaderInfoLog(fragmentShader, 1000, 0, infoLog);

		if (vSuccess)
		{
			std::cout << "Fragment Shader is okk" << std::endl;
		}
		else
		{
			std::cout << "Error in Fragment Shader: " << infoLog;
		};
		int program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		glUseProgram(program);

		/*
		float left = 0;
		float right = 600;
		float bottom = 0;
		float top = 400;

		float mat4[16] = {
			2/(right-left), 0, 0, 0,
			0, 2/(bottom-top), 0, 0,
			0, 0, 1, 0,
			-(right+left)/(right-left), -(bottom+top)/(bottom-top), 0, 1
		};

		float model[16] = {
			200, 0, 0, 0,
			0, 200, 0, 0,
			0, 0, 1, 0,
			100, 100, 0, 1
		};
		*/

		/*
		float positons[] =
		{
			0.0f,0.0f,0.0f,  1.0f,1.0f,0.0f,
			0.0f,1.0f,0.0f,  1.0f,1.0f,0.0f,
			1.0f,1.0f,0.0f,  1.0f,1.0f,0.0f,

			1.0f,1.0f,0.0f,  1.0f,0.0f,1.0f,
			1.0f,0.0f,0.0f,  1.0f,0.0f,1.0f,
			0.0f,0.0f,0.0f,  1.0f,1.0f,0.0f,
		}; 
		*/

		float positons[] =
		{
			0.0f,0.5f,  0.0f,  1.0f,0.0f,1.0f,
		   -0.5f,0.0f,  0.5f,  1.0f,0.0f,1.0f,
			0.5f,0.0f,  0.5f,  1.0f,0.0f,1.0f,
			
			0.0f,0.5f,  0.0f,  1.0f,1.0f,1.0f,
		   -0.5f,0.0f, -0.5f,  1.0f,1.0f,1.0f,
			0.5f,0.0f, -0.5f,  1.0f,1.0f,1.0f,

			0.0f,0.5f,  0.0f,  1.0f,0.0f,0.4f,
		    0.5f,0.0f,  0.5f,  1.0f,0.0f,0.4f,
			0.5f,0.0f, -0.5f,  1.0f,0.0f,0.4f,
			
			0.0f,0.5f,  0.0f,  1.0f,1.0f,0.4f,
		   -0.5f,0.0f,  0.5f,  1.0f,1.0f,0.4f,
		   -0.5f,0.0f, -0.5f,  1.0f,1.0f,0.4f,

		   -0.5f,0.0f,-0.5f,   1.0f,0.0f,0.0f,
		   -0.5f,0.0f, 0.5f,   0.0f,1.0f,0.0f,
			0.5f,0.0f, 0.5f,   0.0f,0.0f,1.0f,

		    0.5f,0.0f, 0.5f,   0.0f,0.0f,1.0f,
			0.5f,0.0f,-0.5f,   0.0f,1.0f,0.0f,
		   -0.5f,0.0f,-0.5f,   1.0f,0.0f,0.0f,

		};

		glm::vec3 cubePositions[] = 
		{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f),

		glm::vec3(1.0f, 0.0f, -2.0f),
		glm::vec3(2.1f, 5.0f, -15.0f),
		glm::vec3(-1.9f, -4.2f, -4.5f),
		glm::vec3(-4.8f, -3.0f, -12.3f),
		glm::vec3(4.4f, -2.4f, -5.5f),
		glm::vec3( 1.7f, 9.0f, -6.5f),
		glm::vec3(8.3f, -8.0f, -7.5f),
		glm::vec3(7.5f, 8.0f, -8.5f),
		glm::vec3(5.5f,-0.2f, -9.5f),
		glm::vec3(-2.3f, 1.0f, -1.0f)
		};


		unsigned int vertexAttribObject, buffer;
		glGenVertexArrays(1, &vertexAttribObject);
		glBindVertexArray(vertexAttribObject);

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positons), positons, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);

		glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
		glfwSwapInterval(1);

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glUseProgram(program);

			glm::mat4 proj = glm::mat4(1.0f);
			proj = glm::perspective(glm::radians(45.0f), window_width/window_height, 0.1f,100.0f);
			//proj = glm::ortho( 0.0f, window_width, window_height, 0.0f);
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				*fValue -= 0.5;
				std::cout << f << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				*fValue += 0.5;
				std::cout << f << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				*xValue -= 0.5;
				std::cout << x << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			{
				*xValue += 0.5;
				std::cout << x << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			{
				*yValue += 0.5;
				std::cout << y << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				*yValue -= 0.5;
				std::cout << y << std::endl;
			}
			///////////////
			const float radius = 10;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
		
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(x, y, f));
			view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f,0.0f));


			int vLoc = glGetUniformLocation(program, "view");
			glad_glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));

		
			//model = glm::scale(model, glm::vec3(200, 200, 0));
			//model = glm::translate(model,glm::vec3(1.0f,0.5f,-3.0f));

			float pLoc = glGetUniformLocation(program, "proj");
			glad_glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(proj));
			
		
			for (int i = 0; i < 20; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);

				model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.05f, 0.8f, 1.0f));

				int mLoc = glGetUniformLocation(program, "model");
				glad_glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLES, 0, 54);

			}; 

			glfwSwapBuffers(window);
			glfwPollEvents();
		};

		glfwTerminate();

		return 07;
	}