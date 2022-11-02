#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.hpp"
#include "timer.hpp"
#include "jello.hpp"
#include "OGL/shader.hpp"
#include "OGL/tetrahedron_mesh.hpp"
#include "OGL/ground_mesh.hpp"

int default_src_width  = 1600;
int default_src_height = 1000;

float refresh_interval = (1/30);

// View parameters
float theta = 0.0;
float phi = 0.0;
float camradius = 5.0;
float cameraspeed = 0.5;

float camX = camradius;
float camY = 0.0;
float camZ = 0.0;

// Allow window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Keyboard input: JKIL for camera motion (also escape to close window)
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // J key will rotate left
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        theta -= cameraspeed;
        if (theta < 0.0) theta += 360.0;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // L key will rotate right
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        theta += cameraspeed;
        if (theta >= 360.0) theta -= 360.0;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // I key will rotate right
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (phi < 90.0-cameraspeed) phi += cameraspeed;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // K key will rotate right
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (phi > -90.0+cameraspeed) phi -= cameraspeed;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
}


class Renderer
{
private:
    GLFWwindow* window;

    GLuint shaderProgram;
    GLuint fragmentShader;
    GLuint vertexShader;

    GLuint modelLoc;
    GLuint viewLoc;
    GLuint projectionLoc;

    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;

    GLuint ground_vao;          // vertex attribute object
    GLuint ground_mesh_vbo;     // vertex buffer object
    GLuint ground_mesh_ibo;     // index buffer object
    GLuint ground_mesh_color;

    GLuint tetrahedron_vao;
    GLuint tetrahedron_vbo;

    GLuint jello_vao;
    GLuint jello_vbo;
    GLuint jello_ibo;

    glm::mat4 *modelMatrices_1, *modelMatrices_2;

    Timer timer;
    Jello jello;

public:
    Renderer();
    ~Renderer();

    void initialize()
    {
        timer.reset(refresh_interval);
        GLObj::build_ground_mesh();
      
        // modelMatrices_1 = new glm::mat4[BOID_NUMBER - NUM_LEADING_BOIDS];
        // modelMatrices_2 = new glm::mat4[BOID_NUMBER - NUM_LEADING_BOIDS];
        update_position_from_manager();

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(default_src_width, default_src_height, k_project_name, NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
    
        // GLAD manages function pointers for OpenGL, so we want to initialize GLAD before we call any OpenGL function
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
        glViewport(0, 0, default_src_width, default_src_height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Enable depth buffering, backface culling
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glUseProgram(shaderProgram);

        // tetrahedron
        glGenVertexArrays(1, &tetrahedron_vao);
        glBindVertexArray(tetrahedron_vao);
            glGenBuffers(1, &tetrahedron_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, tetrahedron_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLObj::tetrahedron), GLObj::tetrahedron, GL_STATIC_DRAW);
        
        // jello
        glGenVertexArrays(1, &jello_vao);
        glBindVertexArray(jello_vao);
            glGenBuffers(1, &jello_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, jello_vbo);
            glBufferData(GL_ARRAY_BUFFER, jello.mesh_vertices.size()*sizeof(glm::vec3), glm::value_ptr(jello.mesh_vertices[0]), GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            glGenBuffers(1, &jello_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, jello_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, jello.mesh_indices.size() * sizeof(unsigned int), &jello.mesh_indices[0], GL_STATIC_DRAW);

        // ground mesh
        glGenVertexArrays(1, &ground_vao);
        glBindVertexArray(ground_vao);
            glGenBuffers(1, &ground_mesh_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, ground_mesh_vbo);
            glBufferData(GL_ARRAY_BUFFER, GLObj::ground_mesh_vertices.size()*sizeof(glm::vec3), glm::value_ptr(GLObj::ground_mesh_vertices[0]), GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                
            glGenBuffers(1, &ground_mesh_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ground_mesh_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLObj::ground_mesh_indices.size()*sizeof(glm::uvec4), glm::value_ptr(GLObj::ground_mesh_indices[0]), GL_STATIC_DRAW);

        // Declare model/view/projection matrices
        model = glm::mat4(1.0f);
        modelLoc = glGetUniformLocation(shaderProgram, "model");
        view = glm::mat4(1.0f);
        viewLoc = glGetUniformLocation(shaderProgram, "view");
        projection = glm::mat4(1.0f);
        projectionLoc = glGetUniformLocation(shaderProgram, "projection");

        // Set Projection matrix
        projection = glm::perspective(glm::radians(45.0f), 1.0f*default_src_width/default_src_height, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }

    void start_looping()
    {
        while(!glfwWindowShouldClose(window) && !timer.is_time_to_stop())
        {
            processInput(window);
            glfwPollEvents();

            if (timer.is_time_to_draw()) 
            {
                timer.update_next_display_time();
                update_position_from_manager();
                draw();
            }

            // flock_manager_1.compute_acceleration();
            // flock_manager_2.compute_acceleration();
            timer.update_simulation_time();

        }
        delete_GLBuffers();
        glfwTerminate();
    }

    void draw() 
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glEnable(GL_DEPTH_TEST);

        // Set view matrix
        view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // render ground mesh
        glBindVertexArray(ground_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ground_mesh_ibo);
            glDrawElements(GL_LINES, GLObj::ground_mesh_indices.size()*4, GL_UNSIGNED_INT, NULL);


        // render tetrahedron
        glBindVertexArray(tetrahedron_vao);
            glBindBuffer(GL_ARRAY_BUFFER, tetrahedron_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            model = glm::mat4(1.0f);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);

        // glDisable(GL_DEPTH_TEST);
        glfwSwapBuffers(window);
    }


    void update_position_from_manager()
    {
        // boids_ptr_1 = flock_manager_1.get_boids();
        // boids_ptr_2 = flock_manager_2.get_boids();

        // for(int i = 0; i < BOID_NUMBER; i++)
        // {
        //     if(i < NUM_LEADING_BOIDS) continue;
        //     model = glm::mat4(1.0f);
        //     model = glm::translate(model, transform_phy2gl(boids_ptr_1[i]->position[0]));
        //     modelMatrices_1[i - NUM_LEADING_BOIDS] = model;
        // }

        // for(int i = 0; i < BOID_NUMBER; i++)
        // {
        //     if(i < NUM_LEADING_BOIDS) continue;
        //     model = glm::mat4(1.0f);
        //     model = glm::translate(model, transform_phy2gl(boids_ptr_2[i]->position[0]));
        //     modelMatrices_2[i - NUM_LEADING_BOIDS] = model;
        // }
    }

    void delete_GLBuffers()
    {
        glDeleteVertexArrays(1, &tetrahedron_vao);
        glDeleteBuffers(1, &tetrahedron_vbo);
        glDeleteBuffers(1, &ground_mesh_vbo);
        glDeleteBuffers(1, &ground_mesh_ibo);
        glDeleteProgram(shaderProgram);
    }

};

Renderer::Renderer() {};
Renderer::~Renderer() {};

#endif // RENDERER_H_