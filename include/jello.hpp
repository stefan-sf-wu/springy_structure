#ifndef JELLO_H_
#define JELLO_H_

#include <vector>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>

#include "common.hpp"
#include "OGL/jello_mesh.hpp"

class Jello
{
public:
    std::vector<vertex> vertices;
    std::vector<strut> struts;
    std::vector<unsigned int> mesh_indices;
    std::vector<glm::vec3> mesh_vertices;

public:
    Jello()
    {
        init_vertice_postion();
        build_strut_for_jello();
        mesh_indices = GLObj::link_jelly_mesh_indices();
    };

    ~Jello() {};

private:
    void init_vertice_postion()
    {
        int i, j, k;
        vertex v;   
        strut s;

        v.mass      = k_jello_mass;
        v.force     = {0.0f, 0.0f, 0.0f};
        v.velocity  = {0.0f, 0.0f, 0.0f};

        for (i = 0; i < k_jello_slices + 2; i++)
        {
            for (j = 0; j < k_jello_slices + 2; j++)
            {
                for (k = 0; k < k_jello_slices + 2; k++)
                {
                    v.position = {
                        k_jello_offset[0] + (k / (k_jello_slices + 1)) * k_jello_edge_size,
                        k_jello_offset[1] + (j / (k_jello_slices + 1)) * k_jello_edge_size,
                        k_jello_offset[2] + (i / (k_jello_slices + 1)) * k_jello_edge_size,
                    };
                    vertices.push_back(v);
                }
            }
        }
    }
        
    void build_strut_for_jello()
    {
        int i, j, k;

        int edge_size = (k_jello_slices + 2);
        std::vector<std::vector<bool>> connected(std::pow(edge_size, 3), std::vector<bool>(std::pow(edge_size, 3), false));   // by vertice indices

        // iterate through each voxel
        for (i = 0; i < k_jello_slices + 1; i++)
        {
            for (j = 0; j < k_jello_slices + 1; j++)
            {
                for (k = 0; k < k_jello_slices + 1; k++)
                {
                    build_strut_for_voxel(k, j, i, connected);
                }
            }
        }
    }

    void build_strut_for_voxel(int k, int j, int i, std::vector<std::vector<bool>> &connected)
    {
        int v0 = xyz2index({k,     j,     i    });
        int v1 = xyz2index({k + 1, j,     i    });
        int v2 = xyz2index({k,     j + 1, i    });
        int v3 = xyz2index({k + 1, j + 1, i    });
        int v4 = xyz2index({k,     j,     i + 1});
        int v5 = xyz2index({k + 1, j,     i + 1});
        int v6 = xyz2index({k,     j + 1, i + 1});
        int v7 = xyz2index({k + 1, j + 1, i + 1});

        if(!connected[v0][v1]) { build_strut(v0, v1); connected[v0][v1] = true; }
        if(!connected[v1][v3]) { build_strut(v1, v3); connected[v1][v3] = true; }
        if(!connected[v2][v3]) { build_strut(v2, v3); connected[v2][v3] = true; }
        if(!connected[v0][v2]) { build_strut(v0, v2); connected[v0][v2] = true; }

        if(!connected[v4][v5]) { build_strut(v4, v5); connected[v4][v5] = true; }
        if(!connected[v5][v7]) { build_strut(v5, v7); connected[v5][v7] = true; }
        if(!connected[v6][v7]) { build_strut(v6, v7); connected[v6][v7] = true; }
        if(!connected[v4][v6]) { build_strut(v4, v6); connected[v4][v6] = true; }

        if(!connected[v1][v5]) { build_strut(v1, v5); connected[v1][v5] = true; }
        if(!connected[v3][v7]) { build_strut(v3, v7); connected[v3][v7] = true; }
        if(!connected[v2][v6]) { build_strut(v2, v6); connected[v2][v6] = true; }
        if(!connected[v0][v4]) { build_strut(v0, v4); connected[v0][v4] = true; }

        // cross strut
        build_strut(v1, v2, k_jello_grid_cross_size); connected[v1][v2] = true;
        build_strut(v2, v4, k_jello_grid_cross_size); connected[v2][v4] = true;
        build_strut(v1, v4, k_jello_grid_cross_size); connected[v1][v4] = true;
        build_strut(v4, v7, k_jello_grid_cross_size); connected[v4][v7] = true;
        build_strut(v1, v7, k_jello_grid_cross_size); connected[v1][v7] = true;
        build_strut(v2, v7, k_jello_grid_cross_size); connected[v2][v7] = true;

        // if(!connected[v1][v2]) { build_strut(v1, v2); connected[v1][v2] = true; }
        // if(!connected[v2][v4]) { build_strut(v2, v4); connected[v2][v4] = true; }
        // if(!connected[v1][v4]) { build_strut(v1, v4); connected[v1][v4] = true; }
        // if(!connected[v4][v7]) { build_strut(v4, v7); connected[v4][v7] = true; }
        // if(!connected[v1][v7]) { build_strut(v1, v7); connected[v1][v7] = true; }
        // if(!connected[v2][v7]) { build_strut(v2, v7); connected[v2][v7] = true; }
    }

    void build_strut(int v0, int v1, float rest_length = k_jello_grid_size)
    {
        strut s;
        s.k_damping     = k_damping_coeff;
        s.k_spring      = k_spring_coeff;
        s.k_rest_length = rest_length;
        s.vertex_indices.push_back(v0);
        s.vertex_indices.push_back(v1);

        struts.push_back(s);
    }
};



#endif // JELLO_H_