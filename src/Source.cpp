#include "glad/glad.h"
#include "glfw3.h"
#include "glad.c"
#include "Shader.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "img.h"

int window_width = 600;
int window_height = 400;
const char * window_title = "3D";

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
	glGetShaderInfoLog(vertexShader, 1000,0, infolog);

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

	float positons[] =
	{
		 0.0f,  1.0f, 1.0f,0.0f,0.0f,  0.0f,0.0f,
		-1.0f, -1.0f, 0.0f,1.0f,0.0f,  1.0f,0.0f,
		 1.0f, -1.0f, 0.0f,0.0f,1.0f,  0.5f,1.0f
	};

	unsigned int vertexAttribObject,buffer;
	glGenVertexArrays(1, &vertexAttribObject);
	glBindVertexArray(vertexAttribObject);
	
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positons), positons, GL_STATIC_DRAW); 
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)8);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)20);

	int imgWidth, imgHeight, ColorChannels;
	unsigned char* imgData = stbi_load("dep/komi.png", &imgWidth, &imgHeight, &ColorChannels,0);

	if (imgData)
	{
		stbi_set_flip_vertically_on_load(true);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, NULL, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);

		std::cout << imgWidth * imgHeight << std::endl;
	}
	else
	{
		std::cout << "failed in image data" << std::endl;
	};

	stbi_image_free(imgData);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.6f, 0.2f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	};
	
	glfwTerminate();
}