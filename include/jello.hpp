#ifndef JELLO_H_
#define JELLO_H_

#include <vector>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>

#include "common.hpp"

class Jello
{
public:
    std::vector<vertex> jello_vertices;
    std::vector<strut> jello_struts;
public:
    Jello()
    {
        // init_jello_vertice_postion();
        build_jello_struts();
    };

    ~Jello() {};

private:
    void init_jello_vertice_postion()
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
                    jello_vertices.push_back(v);
                }
            }
        }
    }
        
    void build_jello_struts()
    {
        int i, j, k;

        int edge_size = (k_jello_slices + 2);
        std::vector<std::vector<bool>> connected(std::pow(edge_size, 3), std::vector<bool>(std::pow(edge_size, 3), false));   // by vertice indices

        // iterate through each subcube
        for (i = 0; i < k_jello_slices + 1; i++)
        {
            for (j = 0; j < k_jello_slices + 1; j++)
            {
                for (k = 0; k < k_jello_slices + 1; k++)
                {
                    build_strut_for_subcube(k, j, i, connected);
                }
            }
        }

        for(auto i : connected)
        {
            for(auto j : i)
            {
                std::cout << j << ' ' ;
            }
            std::cout << std::endl;
        }
    }

    void build_strut_for_subcube(int k, int j, int i, std::vector<std::vector<bool>> &connected)
    {
        int v0 = xyz2index({k,     j,     i});
        int v1 = xyz2index({k + 1, j,     i});
        int v2 = xyz2index({k,     j + 1, i});
        int v3 = xyz2index({k + 1, j + 1, i});
        int v4 = xyz2index({k,     j,     i + 1});
        int v5 = xyz2index({k + 1, j,     i + 1});
        int v6 = xyz2index({k,     j + 1, i + 1});
        int v7 = xyz2index({k + 1, j + 1, i + 1});

        if(!connected[v0][v1]) { build_strut_for_vertices(v0, v1); connected[v0][v1] = true; }
        if(!connected[v1][v3]) { build_strut_for_vertices(v1, v3); connected[v1][v3] = true; }
        if(!connected[v2][v3]) { build_strut_for_vertices(v2, v3); connected[v2][v3] = true; }
        if(!connected[v0][v2]) { build_strut_for_vertices(v0, v2); connected[v0][v2] = true; }

        if(!connected[v4][v5]) { build_strut_for_vertices(v4, v5); connected[v4][v5] = true; }
        if(!connected[v5][v7]) { build_strut_for_vertices(v5, v7); connected[v5][v7] = true; }
        if(!connected[v6][v7]) { build_strut_for_vertices(v6, v7); connected[v6][v7] = true; }
        if(!connected[v4][v6]) { build_strut_for_vertices(v4, v6); connected[v4][v6] = true; }

        if(!connected[v1][v5]) { build_strut_for_vertices(v1, v5); connected[v1][v5] = true; }
        if(!connected[v3][v7]) { build_strut_for_vertices(v3, v7); connected[v3][v7] = true; }
        if(!connected[v2][v6]) { build_strut_for_vertices(v2, v6); connected[v2][v6] = true; }
        if(!connected[v0][v4]) { build_strut_for_vertices(v0, v4); connected[v0][v4] = true; }

        // cross strut
        build_strut_for_vertices(v1, v2); connected[v1][v2] = true;
        build_strut_for_vertices(v2, v4); connected[v2][v4] = true;
        build_strut_for_vertices(v1, v4); connected[v1][v4] = true;
        build_strut_for_vertices(v4, v7); connected[v4][v7] = true;
        build_strut_for_vertices(v1, v7); connected[v1][v7] = true;
        build_strut_for_vertices(v2, v7); connected[v2][v7] = true;

        // if(!connected[v1][v2]) { build_strut_for_vertices(v1, v2); connected[v1][v2] = true; }
        // if(!connected[v2][v4]) { build_strut_for_vertices(v2, v4); connected[v2][v4] = true; }
        // if(!connected[v1][v4]) { build_strut_for_vertices(v1, v4); connected[v1][v4] = true; }
        // if(!connected[v4][v7]) { build_strut_for_vertices(v4, v7); connected[v4][v7] = true; }
        // if(!connected[v1][v7]) { build_strut_for_vertices(v1, v7); connected[v1][v7] = true; }
        // if(!connected[v2][v7]) { build_strut_for_vertices(v2, v7); connected[v2][v7] = true; }
    }

    void build_strut_for_vertices(int v0, int v1)
    {
        strut s;
        s.k_damping     = k_damping_coeff;
        s.k_spring      = k_spring_coeff;
        s.k_rest_length = compute_rest_length(index2xyz(v0), index2xyz(v1));
        s.vertex_indices.push_back(v0);
        s.vertex_indices.push_back(v1);

        jello_struts.push_back(s);
    }

    float compute_rest_length(glm::vec3 xyz1, glm::vec3 xyz2)
    {
        float sum = std::pow(k_jello_cube_edge_size * (xyz1[0] - xyz2[0]), 2) 
            + std::pow(k_jello_cube_edge_size * (xyz1[1] - xyz2[1]), 2) 
            + std::pow(k_jello_cube_edge_size * (xyz1[2] - xyz2[2]), 2);
        return std::pow(sum, 1/2);
    }
};



#endif // JELLO_H_