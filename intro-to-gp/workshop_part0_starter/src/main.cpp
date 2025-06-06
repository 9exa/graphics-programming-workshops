#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>
#include <array>

using namespace glm;

enum {
    CGS_OK,
    CGS_ERR,
};

GLFWwindow* createWindow() {
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "GP Intro", NULL, NULL);
    if (!window) {
        return NULL;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    return window;
}

struct VertexData {
    // Each vertex has own color and pos
    vec3 pos;
    vec3 col;

    VertexData(vec3 pos, vec3 col): pos(pos), col(col) {}
};

/// The indices of the vertex of a tri
typedef GLuint VertexIndex[3];


int setupOpenGL() {
	// We're using OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    
    if (!glfwInit()) {
        return CGS_ERR;
    }
    return 0;
}

int cleanupOpenGL() {
    glfwTerminate();
    return 0;
}

GLuint loadVertexShader(const char *file_path) {
    std::ifstream f;
    f.open(file_path);
    
    std::stringstream source;
    source << f.rdbuf();
    std::string source_string = source.str();
    const char *source_cstr = source_string.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &(source_cstr), NULL);
    glCompileShader(vertex_shader);

    return vertex_shader;
}


GLuint loadFragmentShader(const char *file_path) {
    std::ifstream f;
    f.open(file_path);
    
    std::stringstream source;
    source << f.rdbuf();
    std::string source_string = source.str();
    const char *source_cstr = source_string.c_str();

    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &(source_cstr), NULL);
    glCompileShader(shader);

    return shader;
}


int main() {
	// Tell GLFW what version of OpenGL we are using 

    if (setupOpenGL() != CGS_OK) {
        return -1;
    }

    
    GLFWwindow* window = createWindow();
    if (!window) {
        return -1;
    }

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        return -1;
    }


    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen

        // Swap the buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
