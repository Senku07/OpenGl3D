#pragma once

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec4 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"

"uniform mat4 proj;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"

"out vec4 ourColor;\n"

"void main()\n"
"{\n"
"gl_Position = proj * view * model * vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"ourColor = vec4(aColor.x,aColor.y,aColor.z,1.0f);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"

"out vec4 FragColor;\n"
"in vec4 ourColor;\n"

"void main()\n"
"{\n"
//"FragColor = texture(uniTexture,ourTexture) * ourColor;\n"
"FragColor = ourColor;\n"
//"FragColor = vec4(1.0f,0.0f,0.0f,1.0f);\n"
"}\0";