DEST = Bird
SOURCE_FILES = src/*.cpp
DEST_PATH = ./out
INCLUDES = -I ./include
LIBRARIES = -L ./lib
LINKS = -lraylib -lgdi32 -lwinmm

FLAGS = $(INCLUDES) $(LIBRARIES) $(LINKS) 

clang:
	clang++ $(FLAGS) --target=x86_64-w64-windows-gnu $(SOURCE_FILES) -o $(DEST_PATH)/$(DEST)

gcc:
	g++ $(SOURCE_FILES) -o $(DEST_PATH)/$(DEST) $(FLAGS)