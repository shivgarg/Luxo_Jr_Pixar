all:depth.cpp texture.cpp terrain.cpp Vector3D.cpp
	g++ -w depth.cpp terrain.cpp texture.cpp Vector3D.cpp -lGL -lGLU -lglut -O2 -Ofast -o simulation
