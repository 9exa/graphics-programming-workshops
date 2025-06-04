#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

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

    // Initialeze the GL Viewport
    glViewport(0, 0, 800, 600);

    // Create the Vertex Shader
    GLuint vertex_shader = loadVertexShader("assets/vertex.glsl");
    
    // Create and compile a Fragment Shader
	GLuint fragment_shader = loadFragmentShader("assets/fragment.glsl");


    // Create Shader Program Object and get its reference
	GLuint shader_program = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shader_program);

	// Delete the Shader objects because we no longer need them on the cpu
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


    // Vertices coordinates
    vec3 red = { 1.0f, 0.0, 0.0 };
    vec3 green = { 0.0, 1.0f, 0.0 };
    vec3 blue = { 0.0f, 0.0f, 1.0f };
    vec3 purple = { 0.4f, 0.05f, 0.6f };
    VertexData vertices[] = { 
		VertexData({ 0.5f, 0.5f, 0.0f }, red), // Upper left corner
		VertexData({ 0.5f, -0.5, 0.0f }, blue), // Lower right corner
		VertexData({ -0.5f, 0.5f, 0.0f }, purple), // Upper right corner
		VertexData({ -0.5f, -0.5f, 0.0f }, green), // Lower left corner
    };
    size_t n_vertices = sizeof(vertices) / sizeof(VertexData);
    
    VertexIndex indices[] = {
        { 0, 1, 2 },
        { 1, 2, 3 }
    };

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(3 * sizeof(float)));
	

    // Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
    
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    
    // Create the time uniform
    GLuint time_uid = glGetUniformLocation(shader_program, "time");
    auto start_time = std::chrono::system_clock::now();
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
		glUseProgram(shader_program);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);

        // Update Uniforms
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<float> time_dur (now - start_time);
        float time = time_dur.count();

        glUniform1f(time_uid, time);


        // Draw the triangles using vertexData and Indices with the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, (void *) indices);

        // Swap the buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Delete all gl objects
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader_program);

    // Delete the shaders. They're useless now in the CPU
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
