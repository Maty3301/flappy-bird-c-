all:
	g++ main.cc src/*.cc -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -o bin/FlappyBird
	./bin/FlappyBird