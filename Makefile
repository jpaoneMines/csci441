CXX = g++
CXX_WARNINGS = -Wall -Wextra -Wno-unused-parameter
CXX_ERRORS =
CXX_STANDARD = -std=c++17
CXX_OPTIMIZATION = -O3

INC_PATH = ./dependencies -I./dependencies/glad/include
LIB_PATH = /usr/local/lib
LIBS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lglfw3

EXAMPLE_SRC_FILES = examples/hudcamera.cpp examples/simpleobjects3.cpp examples/simpletri2.cpp
EXAMPLE_OBJECTS = $(EXAMPLE_SRC_FILES:.cpp=.o)
PROGRAMS = $(EXAMPLE_SRC_FILES:examples/%.cpp=bin/%)

help:
	@echo "make <target>"
	@echo "\tdoxygen  - generates doxygen doc files"
	@echo "\texamples - build example programs"
	@echo "\tinstall  - copies to /usr/local/include/"

doxygen:
	doxygen csci441.dox.config

install:
	sudo mkdir -p /usr/local/include/CSCI441
	sudo cp *.hpp /usr/local/include/CSCI441/.
	sudo cp constants.h /usr/local/include/CSCI441/.

examples: clean $(PROGRAMS)

glewexamples: CXX += -DMAKE_GLEW_EXAMPLES
glewexamples: LIBS += -lglew
glewexamples: clean $(PROGRAMS)

bin/%: examples/%.cpp
	@echo "Building $@..."
	$(CXX) $(CXX_OPTIMIZATION) $(CXX_WARNINGS) $(CXX_ERRORS) $(CXX_STANDARD) -I$(INC_PATH) -o $@ dependencies/glad/src/gl.c $< -L$(LIB_PATH) $(LIBS)
	@echo "...done!"

clean:
	@rm -f $(PROGRAMS)

.PHONY: help doxygen install examples glewexamples clean