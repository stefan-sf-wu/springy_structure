#ifndef SPRINGY_SYSTEM_MANAGER_H_
#define SPRINGY_SYSTEM_MANAGER_H_

#include <vector>

#include <glm/glm.hpp>
#include <omp.h>

#include "common.hpp"
#include "jello.hpp"
#include "acceleration_operator.hpp"

/**
 * 1. Loop over all particles: accumulate external forces - grav, air drag
 * 2. Loop over all struts: add strut's psring and damper forces to particles on its end
 * 3. Loop over all faces: distributing lift and drag forces
 * 4. Loop over all particles: obtain acceleration by divideing total applied forces by its mass
*/

class SpringySystemManager
{
public:
    Jello jello;

public: 
    SpringySystemManager() {};

    std::vector<unsigned int> &get_jello_mesh_indices()  { return jello.mesh_indices; }
    std::vector<glm::vec3>    &get_jello_mesh_vertices() { return jello.mesh_vertices; }

    void compute_next_state()
    {
        applied_forces_.clear();
        applied_forces_.assign(jello.vertices.size(), glm::vec3({0.0f, 0.0f, 0.0f}));

        compute_external_forces();

        computer_spring_damping_forces();

        update_state();

        // for(int i = 0 ; i < jello.vertices.size(); i++)
        // {
        //     jello.vertices[i].position += glm::vec3({0, 0, -10});
        // }
    }

    void update_jello_mesh_vertices()
    {
        jello.update_mesh_vertices();
    }

    ~SpringySystemManager() {};

private:
    void update_state()
    {
        int i;
        glm::vec3 acc;

        #pragma omp parallel for\
            private(i, acc)
        for (i = 0; i < jello.vertices.size(); i++)
        {
            acc = applied_forces_[i] / jello.vertices[i].mass;

            // update by RK1
            jello.vertices[i].position += k_time_step * jello.vertices[i].velocity;
            jello.vertices[i].velocity += k_time_step * acc;
        }
    }

    glm::vec3 compute_external_forces()
    {
        int i;
        #pragma omp parallel for\
            private(i)
        for (i = 0; i < jello.vertices.size(); i++)
        {
            applied_forces_[i] += AccOp::compute_gravity(jello.vertices[i]);
        }
    }

    glm::vec3 computer_spring_damping_forces()
    {
        int i;
        float curr_length;
        strut s;
        vertex v1, v2;

        glm::vec3 normalize_vec_v1_v2;
        glm::vec3 spring_force_v1_v2;
        glm::vec3 damping_force_v1_v2;

        #pragma omp parallel for\
            private(i, curr_length, s, v1, v2, normalize_vec_v1_v2, spring_force_v1_v2, damping_force_v1_v2)
        for (i = 0; i < jello.struts.size(); i++)
        {
            s  = jello.struts[i];
            v1 = jello.vertices[s.vertex_indices[0]];
            v2 = jello.vertices[s.vertex_indices[1]];

            normalize_vec_v1_v2 = glm::normalize(v2.position - v1.position);
            curr_length = glm::distance(v2.position, v1.position);

            std::cout << "curr " << curr_length << " rest " << s.rest_length << std::endl;

            spring_force_v1_v2 = s.spring_coeff * (curr_length - s.rest_length) * normalize_vec_v1_v2;
            damping_force_v1_v2 = s.damping_coeff * (glm::dot(v1.velocity, v2.velocity)) * normalize_vec_v1_v2;
            
            #pragma omp critcal
            {
                applied_forces_[s.vertex_indices[0]] += spring_force_v1_v2 + damping_force_v1_v2;
                applied_forces_[s.vertex_indices[1]] += -(spring_force_v1_v2 + damping_force_v1_v2);
            }
        }
    }

private:
    std::vector<glm::vec3> applied_forces_;

};

#endif // SPRINGY_SYSTEM_MANAGER_H_