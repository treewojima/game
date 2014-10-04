CC       := clang++
WARNINGS := -Wall -Wnon-virtual-dtor -Wctor-dtor-privacy
CFLAGS   := -c -ggdb3 -std=c++11 $(shell sdl2-config --cflags) $(WARNINGS) -Iinclude -Ilib/include
LFLAGS   := $(shell sdl2-config --libs) -lSDL2_image
PROJDIRS := include src
SOURCES  := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HEADERS  := $(shell find $(PROJDIRS) -type f -name "*.hpp")
OBJECTS  := $(patsubst %.cpp, %.o, $(SOURCES))
DEPFILES := $(patsubst %.cpp, %.dep, $(SOURCES))
TARGET   := sdl

.PHONY: all clean dumpvars

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LFLAGS) $^

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPFILES)
	find . -type f -iname "*~" -exec rm -f {} \;

-include $(DEPFILES)

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) $<
	@#$(CC) -o $@ $(CFLAGS) -MMD -MP -MF $(patsubst %.c, %.dep, $<) $<

