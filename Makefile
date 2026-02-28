DEST = Bird
SOURCE_FILES = src/*.cpp
DEST_PATH = ./out
INCLUDES = -I ./include
LIBRARIES_WIN = -L ./lib/dev-windows
LIBRARIES_LINUX = -L ./lib/dev-linux
LINKS_WIN = -lraylib -lgdi32 -lwinmm
LINKS_LINUX = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

gcc_win:
	g++ $(INCLUDES) $(SOURCE_FILES) -o $(DEST_PATH)/$(DEST) $(LIBRARIES_WIN) $(LINKS_WIN)

gcc_linux:
	g++ $(INCLUDES) $(SOURCE_FILES) -o $(DEST_PATH)/$(DEST) $(LIBRARIES_LINUX) $(LINKS_LINUX)

	