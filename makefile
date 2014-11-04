a:	a.cpp
	g++ a.cpp first.cpp -lGL -lGLU -lglut -O2 -o a
d:	depth.cpp first.cpp terrain.cpp Vector3D.cpp
	g++ depth.cpp terrain.cpp first.cpp Vector3D.cpp -lGL -lGLU -lglut -O2 -Ofast -o d
