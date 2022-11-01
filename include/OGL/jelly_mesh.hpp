#ifndef JELLY_MESH_H
#define JELLY_MESH_H

#include <vector>

#include <glm/glm.hpp>

#include "jelly.hpp"

namespace GLObj
{
std::vector<glm::vec3> jelly_mesh_vertices;
std::vector<glm::uvec4> jelly_mesh_indices;

std::vector<glm::vec3> &get_jelly_mesh_vertices() {return jelly_mesh_vertices;}
std::vector<glm::uvec4> &get_jelly_mesh_indices() {return jelly_mesh_indices;}

void build_jelly_mesh()
{
    int i, j, k;
    for (i = 0; i <= jelly_slices; i++)
    {
        for (j = 0; j <= jelly_slices; j++)
        {
            for (k = 0; k <= jelly_slices; k++)
            {
                if (i == 0 || i == jelly_slices || j == 0 || j == jelly_slices || k == 0 || k == jelly_slices)
                {
                    jelly_mesh_vertices.push_back({
                        jelly_mesh_edge_size * (i / jelly_slices) - (jelly_mesh_edge_size / 2),
                        jelly_mesh_edge_size * (j / jelly_slices) - (jelly_mesh_edge_size / 2),
                        jelly_mesh_edge_size * (k / jelly_slices) - (jelly_mesh_edge_size / 2),
                    });
                }
            }
        }
    }

}

} // namespace GLObj

#endif // JELLY_MESH_H