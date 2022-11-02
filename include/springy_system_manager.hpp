#ifndef SPRINGY_SYSTEM_MANAGER_H_
#define SPRINGY_SYSTEM_MANAGER_H_

#include <vector>

#include <glm/glm.hpp>

#include "common.hpp"
#include "jello.hpp"

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
    SpringySystemManager();

    std::vector<unsigned int> &get_jello_mesh_indices()  { return jello.mesh_indices; }
    std::vector<glm::vec3>    &get_jello_mesh_vertices() { return jello.mesh_vertices; }

    void compute_next_state()
    {
        for(int i = 0 ; i < jello.vertices.size(); i++)
        {
            jello.vertices[i].position += glm::vec3({0, 0, 10});
        }
    }

    void update_mesh_vertex_position()
    {
        jello.update_mesh_vertex_position();
    }

    ~SpringySystemManager();
private:


};

SpringySystemManager::SpringySystemManager() {};
SpringySystemManager::~SpringySystemManager() {};

#endif // SPRINGY_SYSTEM_MANAGER_H_