all:depth.cpp first.cpp terrain.cpp Vector3D.cpp
	g++ -w depth.cpp terrain.cpp first.cpp Vector3D.cpp -lGL -lGLU -lglut -O2 -Ofast -o d
