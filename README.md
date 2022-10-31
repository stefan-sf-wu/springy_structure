

## load image to texture
- [Simple OpenGL Image Library (SOIL)](https://github.com/littlstar/soil)

## load obj
- [learnopengl.com/Model-Loading/Assimp](https://learnopengl.com/Model-Loading/Assimp)
- [The Asset-Importer-Lib Documentation](https://assimp-docs.readthedocs.io/en/latest/)

## note
> glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   
1. layout (location = 0)
2. size of the vertex attribute: 3 -> vec3
3. type of the data
4. if we want the data to be normalized? 
5. size of stride (3 pieces of positional info and 3 pieces of color)