//
//  Shader.h
//  Practice_openGL
//
//  Created by Master on 2020/8/19.
//  Copyright © 2020 ViDAlab. All rights reserved.
//

//#ifndef Shader_h
//#define Shader_h
#include <string>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    std::string vertexString;
    std::string fragmentString;
    const char* vertexSource;
    const char* fragmentSource;
    unsigned int ID;    // Shader program ID
    
    void use();
};

//#endif /* Shader_h */
