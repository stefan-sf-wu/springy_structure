## TODO
- color of jello
- offset calibration of jello

## load image to texture
- [Simple OpenGL Image Library (SOIL)](https://github.com/littlstar/soil)

## load obj
- [learnopengl.com/Model-Loading/Assimp](https://learnopengl.com/Model-Loading/Assimp)
- [The Asset-Importer-Lib Documentation](https://assimp-docs.readthedocs.io/en/latest/)

## note
- glVertexAttribPointer explaination
    > glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   
    1. layout (location = 0)
    2. size of the vertex attribute: 3 -> vec3
    3. type of the data
    4. if we want the data to be normalized? 
    5. size of stride (3 pieces of positional info and 3 pieces of color)

- [depth test](https://learnopengl.com/Advanced-OpenGL/Depth-testing)

- VAO and EBO

<img src=figures/ebo.png alt="ebo" width="800"/>

- Tetrahedra Cube

<img src=figures/tetrahedron-cube.png alt="tcube" width="400">

- [VBO Indexing](http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/)
