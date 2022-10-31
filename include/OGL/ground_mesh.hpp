#ifndef GROUND_MESH_H
#define GROUND_MESH_H

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

namespace GLObj
{

const float slices = 10;

std::vector<glm::vec3> ground_mesh_vertices;
std::vector<glm::uvec4> ground_mesh_indices;

std::vector<glm::vec3> &get_ground_mesh_vertices() {return ground_mesh_vertices;}
std::vector<glm::uvec4> &get_ground_mesh_indices() {return ground_mesh_indices;}


void build_ground_mesh()
{
    float x, y, z;
    int i, j, row1, row2;
    for (j = 0; j <= slices; ++j)
    {
        for (i = 0; i <= slices; ++i)
        {
            x = 2.0f * (i / slices) - 1;
            y = 2.0f * (j / slices) - 1;
            z = 0.0f;
            ground_mesh_vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (j = 0; j < slices; ++j) 
    {
        for (i = 0; i < slices; ++i) 
        {
            row1 =    j  * (slices+1);
            row2 = (j+1) * (slices+1);

            ground_mesh_indices.push_back(glm::uvec4(row1+i, row1+i+1, row1+i+1, row2+i+1));
            ground_mesh_indices.push_back(glm::uvec4(row2+i+1, row2+i, row2+i, row1+i));
        }
    }
}

} // namespace GLObj

#endif // GROUND_MESH_H

// ref: https://stackoverflow.com/questions/58494179/how-to-create-a-grid-in-opengl-and-drawing-it-with-lines

/**
 
  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  GLuint vbo;
  glGenBuffers( 1, &vbo );
  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  glBufferData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

  GLuint ibo;
  glGenBuffers( 1, &ibo );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(glm::uvec4), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  lenght = (GLuint)indices.size()*4;

 

  // draw

  glEnable(GL_DEPTH_TEST);

  glBindVertexArray(vao);

  glDrawElements(GL_LINES, lenght, GL_UNSIGNED_INT, NULL);

  glBindVertexArray(0);

  glDisable(GL_DEPTH_TEST);

 * 
*/