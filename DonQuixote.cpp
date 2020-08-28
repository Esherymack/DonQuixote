// CS370 Assignment 1 - Don Quixote
// Fall 2020

#include <cstdio>
#include "vgl.h"
#include "utils.h"
#include "vmath.h"

#include "glerror_utility.h"
#include "include/glm/glm.hpp"

using namespace vmath;

enum VAO_IDs {Square, Sun, NumVAOs};
enum Buffer_IDs {SqPosBuffer, SqSkyColBuffer, SqGrassColBuffer, SqHouseColBuffer, TriRoofColBuffer, SqIndexBuffer, SunPosBuffer, SunColBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint posCoords = 2;
GLint colCoords = 4;
GLint numSqIndices = 6;
GLint numTriIndices = 3;

// Shader variables
GLuint program;
GLuint vPos;
GLuint vCol;
GLuint model_mat_loc;
const char *vertex_shader = "../trans.vert";
const char *frag_shader = "../trans.frag";


void build_geometry( );
void display( );
void render_scene( );
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);

int main(int argc, char**argv)
{
	// Create OpenGL window
	GLFWwindow* window = CreateWindow("Don Quixote");
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    } else {
        printf("OpenGL window successfully created\n");
    }

    // TODO: Register callbacks


	// Create geometry buffers
    build_geometry();
    
    // Load shaders and associate variables
    ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, NULL} };
    program = LoadShaders(shaders);
    vPos = glGetAttribLocation(program, "vPosition");
    vCol = glGetAttribLocation(program, "vColor");
    model_mat_loc = glGetUniformLocation(program, "model_matrix");

	// Start loop
    while ( !glfwWindowShouldClose( window ) ) {
    	// Draw graphics
        display();
        // Update other events like input handling
        glfwPollEvents();
        //  TODO: Update angle based on time for fixed rpm when animating

        // Swap buffer onto screen
        glfwSwapBuffers( window );
    }

    // Close window
    glfwTerminate();
    return 0;
}

void build_geometry( )
{
    // Generate and bind vertex arrays
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Square]);

    // Define square vertices
    GLfloat sqVertices[][2] = {
            { 1.0f, 1.0f},
            {-1.0f, 1.0f},
            {-1.0f,-1.0f},
            { 1.0f,-1.0f},
    };

    // TODO: Define gradient colors

    // TODO: Define solid colors

    // TODO: Define face indices (ensure proper orientation)

    // Generate vertex buffers
    glGenBuffers(NumBuffers, Buffers);

    // TODO: Bind square vertex and color buffers

    // TODO: Bind square indices

    // Create sun
    glBindVertexArray(VAOs[Sun]);
    // TODO: Define sun vertices and colors

    // TODO: Bind sun vertex and color buffers

}

void display( )
{
	// Clear window
	glClear(GL_COLOR_BUFFER_BIT);

    // Render objects
	render_scene();

	// Flush pipeline
	glFlush();
}

void render_scene( ) {
    // TODO: Declare transformation matrices

    // Select shader program
    glUseProgram(program);

    // TODO: Draw squares

    // TODO: Draw sky

    // TODO: Draw Grass

    // TODO: Draw House

    // TODO: Draw Roof (using first three square vertices)

    // TODO: Draw fan (using first three square vertices)

    // Set transformation matrix for first blade

    // Set transformation matrix for second blade

    // Set transformation matrix for third blade

    // TODO: Draw sun (using triangle fan)

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO: Start/Stop animation with spacebar

}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){
    // TODO: Flip spin direction with mouse click

}

