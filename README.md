# Cherno OpenGL Tutorial

This is a git resposity filled with OpenGL code which will follow Cherno OpenGL tutorials on Youtube.
The point here is to copy what he does, change, break and learn then continue on the the next video.
So the code itself will deviate from the tutorials to some degree. 

Credit goes to Yan Chernikov (The Cherno)

## Current Differences

This is a list of the current major differences between my code and Youtubes videos.
I am going to be using SDL instead of GLFW for creating a context for OpenGL to render in and user input.
I will also be using CMake to be configure my development environment.
Everything is in the gust namespace.
Abstracted the main loop and set up to a class.
Abstracted the shader to it's own class.

### Current OpenGL Video
I am currently up to the: How I Deal with Shaders in OpenGL Video 8