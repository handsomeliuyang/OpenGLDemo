//
//  triangle.hpp
//  OpenGLDemo
//
//  Created by ly on 2019/5/30.
//  Copyright © 2019 ly. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

namespace triangle {
    int main(int argc, const char * argv[]);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
}

#endif /* triangle_hpp */
