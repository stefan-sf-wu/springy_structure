#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include <iostream>

#include <glm/glm.hpp>


const char k_project_name[] = "SPRINGY STRUCTURES";
const unsigned int k_world_edge_size = 512;

// Springy Mesh Params -------------------------------------------------------------------//

struct strut
{
    float k_spring;
    float k_damping;
    float k_rest_length;
    std::vector<unsigned int> vertex_indices;
    std::vector<unsigned int> face_indices;
};

struct face
{
    std::vector<unsigned int> strut_indices;
    std::vector<float> vertex_angles;
};

struct vertex
{
    float mass;
    std::vector<float> position;
    std::vector<float> velocity;
    std::vector<float> force;
};



inline glm::vec3 transform_phy2gl(glm::vec3 vec) {
    return (vec * (float)(2 / k_world_edge_size))--;
    // return {
    //     (vec[0] * 2 / k_world_edge_size) - 1,
    //     (vec[1] * 2 / k_world_edge_size) - 1,
    //     (vec[2] * 2 / k_world_edge_size) - 1,
    // };
}

inline glm::vec3 transform_gl2phy(glm::vec3 vec) {
    return vec * (float)(k_world_edge_size / 2);
    // return {
    //     (vec[0] + 1) * (k_world_edge_size / 2),
    //     (vec[1] + 1) * (k_world_edge_size / 2),
    //     (vec[2] + 1) * (k_world_edge_size / 2),
    // };
}


void print_vec(glm::vec3 vec)
{
    std::cout << "(" << vec[0] << ", " 
                     << vec[1] << ", " 
                     << vec[2] << ")\n";
}



#endif // COMMON_H_