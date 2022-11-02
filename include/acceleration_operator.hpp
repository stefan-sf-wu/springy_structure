#ifndef ACCELERATION_OPERATORS_H_
#define ACCELERATION_OPERATORS_H_

#include <cmath>
#include <vector>

#include <omp.h>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include "common.hpp"

namespace AccOp
{

// GRAVITY -------------------------------------------------------------------------//
glm::vec3 compute_gravity(vertex &v)
{
    return v.mass * k_gravity ;
}

// SPRING & DAMPING ----------------------------------------------------------------//




} // namespace AccOp

#endif // ACCELERATION_OPERATORS_H_