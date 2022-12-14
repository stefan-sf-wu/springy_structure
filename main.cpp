/* Sample code for drawing box and ball.  
   Much of the basics taken directly from learnopengl.com */

/* Need to install glad, GLFW, and glm first */
/* See learnopengl.com for setting up GLFW and glad */
/* You can just copy the headers from glm, or go through the install */
#include <iostream>

#include "renderer.hpp"
#include "common.hpp"
#include "OGL/jello_mesh.hpp"
#include <vector>
#include "jello.hpp"
#include "glm/glm.hpp"


int main() 
{
    Renderer renderer;
    renderer.initialize();
    renderer.start_looping();
	return 0;
}

/**
 *    (\_/)
 *    ( •_•)
 *    / > ❀
 * 
 */