# Object/Include directories
oPath = ./
iPath = ./

# Paths
paths = -I./$(iPath)

# OS Detection
ifdef SystemRoot

links =
flags = -D 'OCL_WINDOWS'

else

ifeq ($(shell uname -s),Darwin)

links = -framework OpenCL -framework Accelerate -lm
flags = -D 'OCL_OSX'

else

links = -lOpenCL -lm
flags = -D 'OCL_LINUX'

endif
endif

# Substitutes files with the includes/objects paths
mainSource = example1.cpp
sources    = ocl.cpp
includes   = $(addprefix $(iPath)/,$(sources))
objects    = $(addprefix $(oPath)/,$(sources:.cpp=.o))

main: $(objects) $(mainSource)
	g++ $(flags) -g $(paths) $(links) $(objects) $(mainSource) -o main

$(oPath)/%.o:$(iPath)/%.cpp
	g++ $(flags) -g -c $(paths) $< -o $(subst $(iPath),$(oPath),$(<:.cpp=.o))

clean:
	rm $(oPath)/*.o;
