//
//  Learn_openGL.cpp
//  Learn_openGL
//
//  Created by Master on 2020/8/16.
//

# include <iostream>
# include <GL/glew.h> //Using GLEW (but Learn_File is using GLAD)
# include <GLFW/glfw3.h> // GLFW : gernerate window

//Vertex data[]
float vertices[] = {
    // first triangle
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
    // second triangle
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.8f, 0.8f, 0.0f
};

//vertexShader in GLSL (Shading Language)
const char* vertexShaderSource =
"#version 330 core                                                \n"
"layout (location = 0) in vec3 aPos;                              \n"
"void main(){                                                     \n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}            \n";

//fragmentShader in GLSL (Shading Language)
const char* fragmentShaderSource =
"#version 330 core                                                \n"
"out vec4 FragColor;                                              \n"
"void main(){                                                     \n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}                   \n";

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    //Init GLFW
    glfwInit();
    //Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //major-version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); //minor-version(consider compat)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //openGL using core_profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For Mac OS (consider compat)
    
    //Create GLFW window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "OPENGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Err : Failed to create GLFW window.");
        glfwTerminate(); //Terminate GLFW
        return -1;
    }

    //Binding window and context
    glfwMakeContextCurrent(window); //Configure window's context is main context.
    
    //Init GLEW (Now using GLEW replace using GLAD)
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Err : Failed init GLEW.");
        glfwTerminate();
        return -1;
    }
    
    //Set window display location
    glViewport(0, 0, 800, 600);
    
    //Step1: Generate VAO & Bind VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); //generate VAO
    glBindVertexArray(VAO); //Bind VAO
    
    //Step2-1: Generate VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO); //generate VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Step2-2: Bind VBO on the VAO : copy user-defined data into the currently bound buffer (CPU to GPU)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //Create->Attach->Compiling on vertexShader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //Create->Attach->Compiling on fragmentShader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    //Shader progarm : Combined multi-shaders and link the progarm.
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //Linking Vertex Attibutes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //Enable vertex attibutes
    
    
    //Ready engines(keep drawing until stop program)
    while (!glfwWindowShouldClose(window)) //render loop window
    {
        processInput(window); // load function before events trigger
        
        //rendering commands
        glClearColor(0, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //draw the triangle
        glBindVertexArray(VAO); //Bind VAO
        glUseProgram(shaderProgram); //To rander an object
        //draw the object
        //glDrawArrays(GL_TRIANGLES, 0, 3); // last argument: 3 vertices(triangle)
        glDrawArrays(GL_TRIANGLES, 0, 6); // 6 vertices(Two triangles replace rectangle)
        
        glfwSwapBuffers(window); //Swap color buffer for each piexls and show output to screen.
        glfwPollEvents(); // Check any events are triggered.(like keyboard or mouse events)
    }
    
    //Exit render loop and clean all GLFW's resources
    glfwTerminate();
    return 0;
}


  

