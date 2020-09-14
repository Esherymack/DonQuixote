// CS370 Assignment 1 - Don Quixote
// Fall 2020

#include <cstdio>
#include "vgl.h"
#include "utils.h"
#include "vmath.h"

#include "glerror_utility.h"

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

void drawCircle(int triangleCount, GLfloat x, GLfloat y, GLfloat radius)
{
    GLfloat twicePi = 2.0f * 3.141592;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i < triangleCount; i++)
    {
        glVertex2f(
                x + (radius * cos(i * twicePi / triangleCount)),
                y + (radius * sin(i * twicePi / triangleCount))
        );
    }
    glEnd();
}

void render_scene( )
{
    // Declare transformation matrices
    vmath::mat4 model_matrix;
    vmath::mat4 scale_matrix;
    vmath::mat4 rot_matrix;
    vmath::mat4 trans_matrix;

    // Select shader program
    glUseProgram(program);

    // Draw squares
    glBindVertexArray(VAOs[Square]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqPosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPos);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqSkyColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    // Draw sky
    model_matrix = vmath::mat4::identity();
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numSqIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing sky failed!"));

    // Draw Grass
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqGrassColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    trans_matrix = vmath::translate(0.0f, -3.0f, 0.0f);
    scale_matrix = vmath::scale(1.0f, 0.25f, 1.0f);
    model_matrix = scale_matrix * trans_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);

    glDrawElements(GL_TRIANGLES, numSqIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing grass failed!"));

    // Draw House
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqHouseColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    scale_matrix = vmath::scale(0.25f, 0.25f, 1.0f);
    trans_matrix = vmath::translate(0.0f, -1.5f, 0.0f);
    model_matrix = scale_matrix * trans_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);

    glDrawElements(GL_TRIANGLES, numSqIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing house failed!"));

    // Draw Roof (using first three square vertices)
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriRoofColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    model_matrix = vmath::mat4::identity();

    vmath::vec3 axis = { 0.0f, 0.0f, 1.0f };

    scale_matrix = vmath::scale(0.18f, 0.18f, 1.0f);
    trans_matrix = vmath::translate(0.0f, -0.74f, 0.0f);
    rot_matrix = vmath::rotate(-45.0f, axis);
    model_matrix = scale_matrix * trans_matrix * rot_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);

    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing roof failed!"));

    // Draw fan (using first three square vertices)
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqGrassColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    // Set transformation matrix for first blade
    model_matrix = vmath::mat4::identity();

    

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing fan failed!"));

    // Set transformation matrix for second blade

    // Set transformation matrix for third blade

    // Draw sun (using triangle fan)
    // drawCircle(20, 0.0f, 0.0f, 1.0f);
}

void build_geometry( )
{
    // Generate and bind vertex arrays
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Square]);

    // Define square vertices
    GLfloat sqVertices[][2] =
            {
                { 1.0f, 1.0f},
                {-1.0f, 1.0f},
                {-1.0f,-1.0f},
                { 1.0f,-1.0f}
            };

    // Define gradient colors
    // White to #5593e6
    GLfloat blueGradient[][4] =
            {
                {0.33f, 0.58f, 0.9f, 1.0f},
                {0.33f, 0.58f, 0.9f, 1.0f},
                {1.0f, 1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f, 1.0f}
            };

    // #0a522a to #00d962
    GLfloat greenGradient[][4] =
            {
                    {0.04f, 0.32f, 0.16f, 1.0f},
                    {0.04f, 0.32f, 0.16f, 1.0f},
                    {0.0f, 0.85f, 0.38f, 1.0f},
                    {0.0f, 0.85f, 0.38f, 1.0f},
                    {0.0f, 0.85f, 0.38f, 1.0f},
                    {0.0f, 0.85f, 0.38f, 1.0f}
            };

    // White to #ffe675
    GLfloat yellowGradient[][4] =
            {
                {1.0f, 1.0f, 1.0f, 1.0f},
                {1.0f, 0.97f, 0.46f, 1.0f}
            };

    // Define solid colors
    // #5c4e45
    GLfloat brown[][4] =
            {
                {0.32f, 0.3f, 0.27f, 1.0f},
                {0.32f, 0.3f, 0.27f, 1.0f},
                {0.32f, 0.3f, 0.27f, 1.0f},
                {0.32f, 0.3f, 0.27f, 1.0f},
                {0.32f, 0.3f, 0.27f, 1.0f},
                {0.32f, 0.3f, 0.27f, 1.0f}
            };
    // #a11212
    GLfloat red[][4] =
            {
                {0.63f, 0.07f, 0.07f, 1.0f},
                {0.63f, 0.07f, 0.07f, 1.0f},
                {0.63f, 0.07f, 0.07f, 1.0f}
            };


    // Define face indices (ensure proper orientation)
    GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

    // Generate vertex buffers
    glGenBuffers(NumBuffers, Buffers);

    // Bind square vertex and color buffers
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sqVertices), sqVertices, GL_STATIC_DRAW);
    thigle(EXC_MSG("Binding sqposbuffer failed!"));

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqSkyColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blueGradient), blueGradient, GL_STATIC_DRAW);
    thigle(EXC_MSG("Binding sqskycolbuffer failed!"));


    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqGrassColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(greenGradient), greenGradient, GL_STATIC_DRAW);
    thigle(EXC_MSG("Binding sqgrasscolbuffer failed!"));


    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqHouseColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(brown), brown, GL_STATIC_DRAW);
    thigle(EXC_MSG("Binding sqhousecolbuffer failed!"));

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TriRoofColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(red), red, GL_STATIC_DRAW);
    thigle(EXC_MSG("Binding triroofcolbuffer failed!"));

    // Bind square indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[SqIndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    thigle(EXC_MSG("Binding square index buffers failed!"));

    // Create sun
    glBindVertexArray(VAOs[Sun]);
    // Define sun vertices and colors


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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO: Start/Stop animation with spacebar

}

void mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
    // TODO: Flip spin direction with mouse click

}

int main(int argc, char**argv)
{
    try
    {
        // Create OpenGL window
        GLFWwindow* window = CreateWindow("Don Quixote");
        if (!window)
        {
            fprintf(stderr, "ERROR: could not open window with GLFW3\n");
            glfwTerminate();
            return 1;
        }
        else
        {
            printf("OpenGL window successfully created\n");
        }

        // TODO: Register callbacks


        // Create geometry buffers
        build_geometry();

        // Load shaders and associate variables
        ShaderInfo shaders[] = { {GL_VERTEX_SHADER, vertex_shader},{GL_FRAGMENT_SHADER, frag_shader},{GL_NONE, nullptr} };
        program = LoadShaders(shaders);
        vPos = glGetAttribLocation(program, "vPosition");
        vCol = glGetAttribLocation(program, "vColor");
        model_mat_loc = glGetUniformLocation(program, "model_matrix");

        // Start loop
        while ( !glfwWindowShouldClose( window ) )
        {
            // Draw graphics
            display();
            // Update other events like input handling
            glfwPollEvents();
            //  TODO: Update angle based on time for fixed rpm when animating

            // Swap buffer onto screen
            glfwSwapBuffers( window );
        }
    }
	catch(const std::exception &e)
    {
	    std::cerr << "exception: " << e.what() << "\n";
	    throw;
    }

    // Close window
    glfwTerminate();
    return 0;
}


