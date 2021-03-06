// CS370 Assignment 1 - Don Quixote
// Fall 2020

#include <cstdio>
#include "vgl.h"
#include "utils.h"
#include "vmath.h"

#include "glerror_utility.h"
#include <vector>
#include <algorithm>
#include <numeric>

enum VAO_IDs {Square, Sun, NumVAOs};
enum Buffer_IDs {SqPosBuffer, SqSkyColBuffer, SqGrassColBuffer, SqHouseColBuffer, TriRoofColBuffer, SqIndexBuffer, SunPosBuffer, SunColBuffer, SunIndexBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLint posCoords = 2;
GLint colCoords = 4;
GLint numSqIndices = 6;
GLint numTriIndices = 3;
GLint numSunIndices = 0;

// Shader variables
GLuint program;
GLuint vPos;
GLuint vCol;
GLuint model_mat_loc;

// Animation variables
GLfloat fan_angle_1 = 0.0f;
GLfloat fan_angle_2 = 0.0f;
GLfloat fan_angle_3 = 0.0f;
GLfloat delta = 0.1;
GLdouble elTime = 0.0;
GLdouble curTime = 0.0;
GLdouble rpm = 10.0;
GLint dir = 1;
bool IsMoving = false;

const char *vertex_shader = "../trans.vert";
const char *frag_shader = "../trans.frag";

/* Welcome to "Madison Overcomplicates Everything" */
void drawSun(GLfloat x_origin, GLfloat y_origin, GLfloat radius, GLint numSides)
{
    int numVerts = numSides * 2;
    GLfloat step = 2 * M_PI / ( numVerts + 1 );

    std::vector<GLfloat> vertX;
    std::vector<GLfloat> vertY;

    vertX.push_back(x_origin);
    vertY.push_back(y_origin);

    for(int i = 0; i < numVerts + 1; i++)
    {
        GLfloat x = x_origin + cos(step * i) * radius;
        GLfloat y = y_origin - sin(step * i) * radius;
        vertX.push_back(x);
        vertY.push_back(y);
    }

    std::vector<GLfloat> allVerts;
    for(int i = 0; i < vertX.size(); i++)
    {
        allVerts.push_back(vertX[i]);
        allVerts.push_back(vertY[i]);
    }

    // Create sun
    glBindVertexArray(VAOs[Sun]);

    // Define sun vertices and colors
    std::vector<GLushort> sunIndices(allVerts.size()/2);
    std::iota(sunIndices.begin(), sunIndices.end(), 0);
    sunIndices.push_back(1);

    // White to #ffe675
    std::vector<vmath::vec4> yellowGradient(allVerts.size() / 2);
    std::fill(yellowGradient.begin(), yellowGradient.end(), vmath::vec4(1.0f, 0.97f, 0.46f, 1.0f));
    yellowGradient[0] = vmath::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    // Bind sun vertex and color buffers
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, allVerts.size() * sizeof(GLfloat), allVerts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, yellowGradient.size() * sizeof(vmath::vec4), yellowGradient.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[SunIndexBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sunIndices.size() * sizeof(GLushort), sunIndices.data(), GL_STATIC_DRAW);
    numSunIndices = sunIndices.size();
}

void render_scene( )
{
    // Declare transformation matrices
    vmath::mat4 model_matrix;
    vmath::mat4 scale_matrix;
    vmath::mat4 rot_matrix;
    vmath::mat4 trans_matrix;

    vmath::mat4 animation_matrix;

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
    trans_matrix = vmath::translate(0.0f, -0.7f, 0.0f);
    rot_matrix = vmath::rotate(-45.0f, axis);
    model_matrix = scale_matrix * trans_matrix * rot_matrix;

    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);

    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing roof failed!"));

    // Draw fan (using first three square vertices)
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SqSkyColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    // it was at this point i gave upand went to bed
    vmath::vec4 rotation_axis = { -1.0f, 1.0f, 1.0f, 0.0f};

    rotation_axis = rotation_axis * trans_matrix;

    vmath::vec3 r_axis = vmath::vec3(rotation_axis[0], rotation_axis[1], 1.0f);

    // Set transformation matrix for first blade
    model_matrix = vmath::mat4::identity();
    scale_matrix = vmath::scale(0.1f, 0.3f, 1.0f);
    rot_matrix = vmath::rotate(-33.0f, axis);
    animation_matrix = vmath::rotate(fan_angle_1, axis);
    trans_matrix = vmath::translate(0.24f, 0.33f, 0.0f);

    model_matrix = animation_matrix * trans_matrix * rot_matrix * scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing fan failed!"));

    // Set transformation matrix for second blade
    model_matrix = vmath::mat4::identity();
    scale_matrix = vmath::scale(0.1f, 0.3f, 1.0f);
    rot_matrix = vmath::rotate(50.0f, axis);
    animation_matrix = vmath::rotate(fan_angle_2, axis);
    trans_matrix = vmath::translate(-0.16f, 0.4f, 0.0f);

    model_matrix = animation_matrix * trans_matrix * rot_matrix * scale_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("Drawing fan failed!"));

    // Set transformation matrix for third blade
    model_matrix = vmath::mat4::identity();
    trans_matrix = vmath::translate(0.0f, -0.37f, 0.0f);
    scale_matrix = vmath::scale((sqrt(2.0f)/20.0f), (sqrt(2.0f))/4.0f, 1.0f);
    rot_matrix = vmath::rotate(-45.0f, axis);
    animation_matrix = vmath::rotate(fan_angle_3, axis);

    model_matrix = animation_matrix * trans_matrix * scale_matrix * rot_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);
    glDrawElements(GL_TRIANGLES, numTriIndices, GL_UNSIGNED_SHORT, nullptr);

    // Draw sun (using triangle fan)
    glBindVertexArray(VAOs[Sun]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[SunIndexBuffer]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunPosBuffer]);
    glVertexAttribPointer(vPos, posCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPos);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[SunColBuffer]);
    glVertexAttribPointer(vCol, colCoords, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vCol);

    model_matrix = vmath::mat4::identity();
    trans_matrix = vmath::translate(-0.65f, 0.6f, 0.0f);
    model_matrix = trans_matrix;
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, model_matrix);

    glDrawElements(GL_TRIANGLE_FAN, numSunIndices, GL_UNSIGNED_SHORT, nullptr);
    thigle(EXC_MSG("You can't draw a circle to save your life"));

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

    drawSun(0.0f, 0.0f, 0.2f, 100);

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

    // Start/Stop animation with spacebar
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        IsMoving = !IsMoving;
    }
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
    // Flip spin direction with mouse click
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        dir = dir * -1;
    }


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

        // Register callbacks
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_callback);

        elTime = glfwGetTime();

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
            if(IsMoving)
            {
                // Update angle based on time for fixed rpm when animating
                curTime = glfwGetTime();
                GLdouble dang = rpm * (360.0/60.0) * (curTime - elTime) * dir;
                fan_angle_1 = fan_angle_1 + dang;
                fan_angle_2 = fan_angle_2 + dang;
                fan_angle_3 = fan_angle_3 + dang;
                elTime = curTime;
            }


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


