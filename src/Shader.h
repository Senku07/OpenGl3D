#pragma once

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexture;\n"

"out vec4 ourColor;"
"out vec2 ourTexture;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"ourColor = vec4(aColor.x,aColor.y,aColor.z,1.0);\n"
"ourTexture = aTexture;\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"

"out vec4 FragColor;\n"
"in vec4 ourColor;\n"
"in vec2 ourTexture;\n"
"uniform sampler2D uniTexture;\n"

"void main()\n"
"{\n"
"FragColor = texture(uniTexture,ourTexture);\n"
//"FragColor = ourColor;\n"
"}\0";