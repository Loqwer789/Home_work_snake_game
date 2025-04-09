CXX = g++ #компиллятор

CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 
#флаги компиляции

TARGET =my_snake_game # имя исполняемого файла

SRCS = main.cpp Game.cpp Snake.cpp Food.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS)   -o $@ $^ -lncurses

%.o: %.cpp Game.h Snake.h Food.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET)

