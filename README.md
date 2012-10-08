Wator-Simulation
================
To prepare your system for using OpenGL do the following:

1. Install driver for your graphics card.
	You can get this from your graphics card provider.
	Links for each provider can be found at: 
	http://www.opengl.org/wiki/Getting_Started#Linux

	You can also use the Control Center to install them but the drivers there 		were outdated for mine.

2. Install the header files of OpenGL libraries.
	sudo apt-get update
	sudo apt-get install libgl1-mesa-dev

3. Install the GCC C/C++ compilers and associated tools such as make:
	sudo apt-get install build-essential

4. To make use of GLEW, FreeGLUT and GLM, install the development libraries:
	sudo apt-get install libglew1.5-dev freeglut3-dev libglm-dev

To get information about your OpenGL driver type this into the shell:
	glxinfo | grep OpenGL
