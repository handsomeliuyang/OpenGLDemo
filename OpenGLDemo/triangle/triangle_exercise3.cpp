//
//  triangle_exercise3.cpp
//  OpenGLDemo
//
//  Created by ly on 2019/5/30.
//  Copyright © 2019 ly. All rights reserved.
//

#include "triangle_exercise3.hpp"

namespace triangle_exercise3 {
    
    // 定义常量
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n" // create a variable aPos of type vec3
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // Assign a value to the predefined variable gl_Position, gl_Position is the output of this Shader
    "}\0";
    
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n" // create a out variable of type vec4
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    
    const char *fragmentShaderSource2 = "#version 330 core\n"
        "out vec4 FragColor;\n" // create a out variable of type vec4
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";
    
    int main(int argc, const char * argv[]) {
        
        // 创建GLFW
        glfwInit();
        // 配置GLFW：主版本号(Major)为3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // 配置GLFW：次版本号(Minor)为3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // 配置GLFW：使用核心模式(Core-profile)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // 经过测试，在macOS-10.14.1版本里，此句句柄不能添加
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        
        // 创建窗口
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        // 监听GLFW的窗口变化
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
        // 在调用OpenGL Api之前，需要通过GLAD初始化函数指针
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        
        // build and compile out shader program
        // ------------------------------------
        // vertex shader
        // create empty vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // insert vertex shader source to shader object, the second parameter indicates the number of strings
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        // compile the shader object that attached the source
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Frame Shader
        // create empty frame shader object
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // insert frame shader source to shader object, the second parameter indices the number of strings
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        // compile the frame shader that attached the source
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_FRAGMENT_SHADER, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
        glCompileShader(fragmentShader2);
        glGetShaderiv(fragmentShader2, GL_FRAGMENT_SHADER, &success);
        if(!success) {
            glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        // link shader objects to shader program
        // create a shader program
        int shaderProgram = glCreateProgram();
        // attached a compiled shader object to a shader program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        // links all attached shader object in one shader program
        // During the linking step, each output is matched to each input of shaders and whenever something is not right linking fails.
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        int shaderProgram2 = glCreateProgram();
        glAttachShader(shaderProgram2, vertexShader);
        glAttachShader(shaderProgram2, fragmentShader2);
        glLinkProgram(shaderProgram2);
        glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
        if(success){
            glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        // removes shader object, clearing all allocated memory
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteShader(fragmentShader2);
        
        // set up vertex data and buffer and configure vertex attributes
        // -------------------------------------------------------------
        // 3D coordinates, using one-dimensional array storage
        float vertices[] = {
            0.5f,  0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f,  0.5f, 0.0f  // top left
        };
        float vertices2[] = {
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f  // top left
        };
        
        // Create VAO(Vertex Array Object), VBO(Vertex Buffer Object), EBO(Index Buffer Object)
        // VAO automatically associates VBO and EBO
        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        // When using OpenGL to draw graphics, use vertex array objects, vertex array object associate vertex buffer object and vertex attributes
        glBindVertexArray(VAO);
        
        // binds a vertex buffer object to array buffer type
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // stores vertex data in initialized memory bound to vertex buffer object
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // specifies how OpenGL should interpret the vertex buffer data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        
        // safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        unsigned int VAO2, VBO2;
        glGenVertexArrays(1, &VAO2);
        glGenBuffers(1, &VBO2);
        
        glBindVertexArray(VAO2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        
        // safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        // sets the polygon rasterization mode of how OpenGL should draw its primitives.
        //        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        // Render Loop
        while(!glfwWindowShouldClose(window)){
            // input
            processInput(window);
            
            // Clear the screen with specified color
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Using a shader program
            glUseProgram(shaderProgram);
            // bind the vertex array object
            glBindVertexArray(VAO);
            // Draw a triangle using a vertex array object
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            glUseProgram(shaderProgram2);
            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            // 交换缓存，调用事件
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        
        glfwTerminate();
        return 0;
    }
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        // 设置视口，前两个参数设置左下角的位置
        glViewport(0, 0, width, height);
    }
    
    void processInput(GLFWwindow *window){
        // 点击返回按钮后，关闭窗口
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
    }
    
}
