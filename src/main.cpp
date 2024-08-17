#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
int main()
{

    if(glfwInit() == GLFW_FALSE)
    {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return EXIT_FAILURE;
    }


    int WIDTH = 1920, HEIGHT = 1080;
    GLFWwindow* window;

    window = glfwCreateWindow(WIDTH, HEIGHT, "pbl", 0, 0);
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load OpenGL" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }


    const float points[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    GLuint vbo, vao;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    std::cout << "Error after VBO: " << glGetError() << std::endl;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "Error after VAO: " << glGetError() << std::endl; 

    const char* vertSource = "#version 330 core\n"
    "layout(location = 0) in vec3 pos;\n"
    "void main() {\n"
    "gl_Position = vec4(pos, 1.0);}\0";

    const char* fragSource = "#version 330 core\n"
    "out vec4 FragCol;\n"
    "void main() {\n"
    "FragCol = vec4(1.0);}\0";

    GLuint shaderProg, vertShader, fragShader;

    shaderProg = glCreateProgram();
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertShader, 1, &vertSource, 0);
    glShaderSource(fragShader, 1, &fragSource, 0);

    glCompileShader(vertShader);
    glCompileShader(fragShader);

    glAttachShader(shaderProg, vertShader);
    glAttachShader(shaderProg, fragShader);
    glLinkProgram(shaderProg);

    int success;
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    if(!success)
    {
        std::cout << "Did not compile" << std::endl;
    }


    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProg);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glUseProgram(0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    return 0;
}