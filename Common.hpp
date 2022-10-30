#ifndef COMMON_H_
#define COMMON_H_

#define ENABLE_LOGGER true

const char k_project_name[] = "SPRINGY STRUCTURES";

/**
 * WORLD PARAMS
 */ 
const unsigned int k_world_edge_size = 512;


#define PARTICLE_MASS 1.0
#define BOID_NUMBER 30
#define NUM_LEADING_BOIDS 6

/**
 * FLOCKING 
*/
#define AVOIDANCE_SCALAR 1e2
#define VELOCITY_MATCHING_SCALAR 8e-2
#define CENTERING_SCALAR 1e-2

/**
 * VIEW PARAMS
 */ 
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1000
#define DISPLAY_REFRESH_INTERVAL (1.0 / 30.0) //  sec (HZ)

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

struct Boid
{   
    std::vector<glm::vec3> position;    // For timestep T and timestep T+1
    std::vector<glm::vec3> velocity;    // For timestep T and timestep T+1

    Boid()
    : position({{0, 0, 0}, {0, 0, 0}})
    , velocity({{0, 0, 0}, {0, 0, 0}}) {}
    Boid(std::vector<glm::vec3> pos, std::vector<glm::vec3> vel)
    : position(pos)
    , velocity(vel) {}
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

#if ENABLE_LOGGER
void print_vec(glm::vec3 v)
{
    std::cout << "(" << v[0] << ", "<<v[1]<<", "<<v[2]<<")\n";
}
#endif


#endif // COMMON_H_