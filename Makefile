all:
	g++ -g *.cxx Figures/*.cxx UI/*.cxx -o program -O2 -lsfml-graphics -lsfml-window -lsfml-system
