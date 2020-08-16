//
//  Learn_openGL.cpp
//  Learn_openGL
//
//  Created by Master on 2020/8/16.
//

# include <iostream>
# include <GL/glew.h> //Using GLEW (but Learn_File is using GLAD)
# include <GLFW/glfw3.h> // GLFW : gernerate window

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
    
    //Ready engines(keep drawing until stop program)
    while (!glfwWindowShouldClose(window)) //render loop window
    {
        processInput(window); // load function before events trigger
        
        //rendering commands
        glClearColor(0, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window); //Swap color buffer for each piexls and show output to screen.
        glfwPollEvents(); // Check any events are triggered.(like keyboard or mouse events)
    }
    
    //Exit render loop and clean all GLFW's resources
    glfwTerminate();
    return 0;
}


  

