#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>

const char k_project_name[] = "SPRINGY STRUCTURES";
const int k_world_edge_size = 512;

// Springy Mesh Struct -------------------------------------------------------------------//
struct strut
{
    float k_spring;
    float k_damping;
    float k_rest_length;
    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> face_indices;

    void clear()
    {
        k_spring      = 0.0f;
        k_damping     = 0.0f;
        k_rest_length = 0.0f;
        vertex_indices.clear();
        face_indices.clear();
    }
};

struct face
{
    std::vector<unsigned int> strut_indices;
    std::vector<float> vertex_angles;

    void clear()
    {
        strut_indices.clear();
        vertex_angles.clear();
    }
};

struct vertex
{
    float mass;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 force;
    
    void clear()
    {
        mass     = 0;
        position = {0.0f, 0.0f, 0.0f};
        velocity = {0.0f, 0.0f, 0.0f};
        force    = {0.0f, 0.0f, 0.0f};
    }
};

// Springy Mesh Params -------------------------------------------------------------------//
const float k_jello_mass            = 7; // kg
const float k_jello_edge_size       = 20; // m
const float k_jello_slices          = 0;
const float k_vertex_mass           = (k_jello_mass / std::pow(k_jello_slices + 2, 3)); // kg
const float k_jello_cube_edge_size  = k_jello_edge_size / (k_jello_slices + 1);

const float k_time_constant         = 5; //sec
const float k_undamped_period       = 3;
const float k_damping_coeff         = (2 * k_vertex_mass) / k_time_constant; // N-s/m
const float k_spring_coeff          = (4 * std::pow(M_PI, 2) * k_vertex_mass) / std::pow(k_undamped_period, 2); // N-s/m

const glm::vec3 k_jello_offset = 
{
    -(k_jello_edge_size / 2),
    -(k_jello_edge_size / 2),
    -(k_jello_edge_size / 2)
};


inline int xyz2index(glm::vec3 xyz)
{ 
    return xyz[0] + (k_jello_slices + 2) * xyz[1] + std::pow((k_jello_slices + 2), 2) * xyz[2]; 
}

inline glm::vec3 index2xyz(int index)
{
    glm::vec3 xyz;
    xyz[2] = std::floor(index / std::pow((k_jello_slices + 2), 2));
    index -= xyz[2];
    xyz[1] = std::floor(index / (k_jello_slices + 2));
    index -= xyz[1];
    xyz[0] = index;
    return xyz;
}


// OpenGL -------------------------------------------------------------------//
inline glm::vec3 transform_phy2gl(glm::vec3 vec) { return (vec * (float)(2 / k_world_edge_size))--; }
inline glm::vec3 transform_gl2phy(glm::vec3 vec) { return vec++ * (float)(k_world_edge_size / 2); }

// Debug --------------------------------------------------------------------//
void print_vec(glm::vec3 vec)
{
    std::cout << "(" << vec[0] << ", " 
                     << vec[1] << ", " 
                     << vec[2] << ")\n";
}



#endif // COMMON_H_