#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// CONFIG
float CAMSPEED = 0.5f;
float CAMROTSPEED = 3.f;



float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


std::string readfile(const char* path)
{
    std::fstream fs{path};
    if(!fs.is_open())
    {
        std::cout << "Failed to open file: " << path << std::endl;
        return "";
    }

    std::ostringstream ss;
    ss << fs.rdbuf();

    return ss.str();
}

struct CamTransform
{
    glm::vec3 pos{0.0f};
    glm::vec3 forward{0.0f, 0.0f, 1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};
    glm::vec4 rot{0.0f};

    /**
     * Dont use this
     */
    float camY, camX;
};

void MoveCamera(CamTransform *transform, GLFWwindow *&window)
{
    // Move
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        transform->pos += transform->forward * CAMSPEED;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        transform->pos -= transform->forward * CAMSPEED;

    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        transform->pos -= glm::normalize(glm::cross(transform->forward, transform->up)) * CAMSPEED;

    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        transform->pos += glm::normalize(glm::cross(transform->forward, transform->up)) * CAMSPEED;
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    
    //Look
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        transform->camX += CAMROTSPEED;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        transform->camX -= CAMROTSPEED;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        transform->camY -= CAMROTSPEED;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        transform->camY += CAMROTSPEED;
    }

    glm::vec3 look;
    look.x = cos(glm::radians(transform->camY)) * cos(glm::radians(transform->camX));
    look.y = sin(glm::radians(transform->camX));
    look.z = sin(glm::radians(transform->camY)) * cos(glm::radians(transform->camX));
    transform->forward = look;
}

int main()
{

    if(glfwInit() == GLFW_FALSE)
    {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return EXIT_FAILURE;
    }


    int WIDTH = 1920, HEIGHT = 1080;
    GLFWwindow *window;

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

    glViewport(0, 0, WIDTH, HEIGHT);

    GLuint vbo, vao;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    std::cout << "Error after VBO: " << glGetError() << std::endl;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "Error after VAO: " << glGetError() << std::endl; 

    std::string vert = readfile("../vs/shader.vs");
    std::string frag = readfile("../fs/shader.fs");

    const char* vertSource = vert.c_str();
    const char* fragSource = frag.c_str();

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

    // Initialise Cam
    CamTransform camTransform;



    glm::mat4 proj = glm::perspective(glm::radians(60.0f), WIDTH/(float)HEIGHT, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Cam movement
        MoveCamera(&camTransform, window);
        glm::mat4 view = glm::lookAt(camTransform.pos, camTransform.pos + camTransform.forward, camTransform.up);


        glUseProgram(shaderProg);
        glm::mat4 model = glm::translate(glm::mat4{1}, glm::vec3{0, 0, -3.5f});
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "proj"), 1, GL_FALSE, &proj[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProg, "model"), 1, GL_FALSE, &model[0][0]);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glUseProgram(0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    return 0;
}