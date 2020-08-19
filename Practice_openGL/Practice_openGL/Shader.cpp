//
//  Shader.cpp
//  Practice_openGL
//
//  Created by Master on 2020/8/19.
//  Copyright © 2020 ViDAlab. All rights reserved.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    //input HD file
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    //read file to MEM (declear)
    std::stringstream vertexSStream;
    std::stringstream fragmentSStream;
    
    //open HD file
    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    //vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        if (!vertexFile.is_open() || !fragmentFile.is_open()) {
            throw std::logic_error("open file error");
        }
        
        //rdbuf : HD file load to MEM fileBuffer -> stringBuffer
        vertexSStream << vertexFile.rdbuf();
        fragmentSStream << fragmentFile.rdbuf();
        
        //transform to str()
        vertexString = vertexSStream.str();
        fragmentString = fragmentSStream.str();
        
        vertexSource = vertexString.c_str();
        fragmentSource = fragmentString.c_str();
        
        unsigned int vertex, fragment;
        
        vertex =  glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex); //Binary code
        
        fragment =  glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, NULL);
        glCompileShader(fragment);
        
        ID = glCreateProgram(); // binary exe
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    } catch (const std::logic_error& ex) {
        printf("%s", ex.what());
    }
}

void Shader::use()
{
    glUseProgram(ID);
}
