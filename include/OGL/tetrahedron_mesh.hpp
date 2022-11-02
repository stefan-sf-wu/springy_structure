#ifndef TETRAHEDRON_MESH_H
#define TETRAHEDRON_MESH_H

namespace GLObj
{

float tetrahedron[] =
{
 -0.1f,  0.1f,  0.2f,   1.0f, 0.25f, 0.25f,
  0.1f,  0.5f,  0.8f,   1.0f, 0.25f, 0.25f,
  0.3f,  0.5f,  0.2f,   1.0f, 0.25f, 0.25f,

 -0.1f,  0.1f,  0.2f,   1.0f, 0.45f, 0.45f,
  0.1f,  0.5f,  0.8f,   1.0f, 0.45f, 0.45f,
 -0.3f,  0.7f,  0.5f,   1.0f, 0.45f, 0.45f,

 -0.1f,  0.1f,  0.2f,   1.0f, 0.25f, 0.25f,
  0.3f,  0.5f,  0.2f,   1.0f, 0.25f, 0.25f,
 -0.3f,  0.7f,  0.5f,   1.0f, 0.25f, 0.25f,

  0.1f,  0.5f,  0.8f,   0.8f, 0.25f, 0.25f,
  0.3f,  0.5f,  0.2f,   0.8f, 0.25f, 0.25f,
 -0.3f,  0.7f,  0.5f,   0.8f, 0.25f, 0.25f,
};

} // namespace GLObj

#endif // TETRAHEDRON_MESH_H

/*

-0.1f,  0.1f,  0.2f,    1.0f, 0.25f, 0.25f
 0.1f, 0.5f,  0.8f,   1.0f, 0.25f, 0.25f
 0.3f, 0.5f, 0.2f   1.0f, 0.25f, 0.25f
 -0.3f, 0.7f, 0.5f,   1.0f, 0.25f, 0.25f

1.0f, 0.25f, 0.25f,
0.8f, 0.25f, 0.25f,
1.0f, 0.45f, 0.45f,

*/