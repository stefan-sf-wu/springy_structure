#ifndef JELLY_MESH_H
#define JELLY_MESH_H

#include <vector>

#include <glm/glm.hpp>
#include <omp.h>

#include "jello.hpp"

namespace GLObj
{


void build_flat_map(
    std::vector<std::vector<int>> &flat_map_side,
    std::vector<std::vector<int>> &flat_map_top,
    std::vector<std::vector<int>> &flat_map_bot)
{
    int i = 0, j = 0, k = 0;
    for (; i < k_jello_slices + 2; i++)
    {
        for (; k < k_jello_slices + 2; k++) { flat_map_side[i].push_back(xyz2index({k, j, i})); }
        k = k_jello_slices + 1;
        j++;
        for (; j < k_jello_slices + 2; j++) { flat_map_side[i].push_back(xyz2index({k, j, i})); }
        j = k_jello_slices + 1;
        k--;
        for (; k >= 0; k--) { flat_map_side[i].push_back(xyz2index({k, j, i})); }
        k = 0;
        j--;
        for (; j >= 0; j--) { flat_map_side[i].push_back(xyz2index({k, j, i})); }
        j = 0;
    }

    for (j = 0; j < k_jello_slices + 2; j++)
    {
        for(k = 0; k < k_jello_slices + 2; k++)
        {
            flat_map_bot[j][k] = xyz2index({k, j, 0});
            flat_map_top[j][k] = xyz2index({k, j, (k_jello_slices + 1)});
        }
    }
}

void trace_map_and_push_indice(std::vector<std::vector<int>> &flat_map, std::vector<unsigned int> &jello_mesh_indices)
{
    for (int i = 0; i < flat_map.size() - 1; i++)
    {
        for (int j = 0; j < flat_map[0].size() - 1; j++)
        {
            jello_mesh_indices.push_back(flat_map[i][j]);
            jello_mesh_indices.push_back(flat_map[i+1][j]);
            jello_mesh_indices.push_back(flat_map[i][j+1]);
        }
        for (int j = 1; j < flat_map[0].size(); j++)
        {
            jello_mesh_indices.push_back(flat_map[i + 1][j]);
            jello_mesh_indices.push_back(flat_map[i-1+1][j]);
            jello_mesh_indices.push_back(flat_map[i + 1][j-1]);
        }
    }
}

std::vector<unsigned int> build_jello_mesh_indices()
{
    std::vector<unsigned int> jello_mesh_indices;
    jello_mesh_indices.clear();

    std::vector<std::vector<int>> flat_map_side(k_jello_slices + 2, std::vector<int>());
    std::vector<std::vector<int>> flat_map_top(k_jello_slices + 2, std::vector<int>(k_jello_slices + 2));
    std::vector<std::vector<int>> flat_map_bot(k_jello_slices + 2, std::vector<int>(k_jello_slices + 2));

    build_flat_map(flat_map_side, flat_map_top, flat_map_bot);

    trace_map_and_push_indice(flat_map_side, jello_mesh_indices);
    trace_map_and_push_indice(flat_map_top, jello_mesh_indices);
    trace_map_and_push_indice(flat_map_bot, jello_mesh_indices);


    return jello_mesh_indices;
}

} // namespace GLObj

#endif // JELLY_MESH_H