#ifndef SPRINGY_SYSTEM_MANAGER_H_
#define SPRINGY_SYSTEM_MANAGER_H_

#include <vector>

#include <glm/glm.hpp>

#include "common.hpp"

/**
 * 1. Loop over all particles: accumulate external forces - grav, air drag
 * 2. Loop over all struts: add strut's psring and damper forces to particles on its end
 * 3. Loop over all faces: distributing lift and drag forces
 * 4. Loop over all particles: obtain acceleration by divideing total applied forces by its mass
*/

class SpringySystemManager
{
private:

public: 
    SpringySystemManager();
    ~SpringySystemManager();

    void compute_next_state()
    {

    }

    void build_jelly()
    {

    }
};

SpringySystemManager::SpringySystemManager() {};
SpringySystemManager::~SpringySystemManager() {};

#endif // SPRINGY_SYSTEM_MANAGER_H_