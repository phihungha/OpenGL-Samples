#include <iostream>

#include <shader.h>
#include <window.h>

int main()
{
    GLFWwindow* window = initWindow(800, 600, "Triangles");

    ShaderProgram shader = ShaderProgram::fromFiles("vertex_shader.glsl", "fragment_shader.glsl");


}
