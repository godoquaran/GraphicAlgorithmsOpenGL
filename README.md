# GraphicsAlgorithmsOpenGL
* Graphics Algorithms in OpenGL
1. lineDDA
1. circle

* Software
  1. MSYS2
  2. pacman -S mingw-w64-x86_64-freeglut
  3. pacman -S mingw-w64-x86_64-glew
  4. g++ -c -o alg.o alg.cpp -I/mingw64/include
  5. g++ -o alg alg.o -L/mingw64/lib -lfreeglut -lopengl32 -lglu32 -lglew32 -Wl,--subsystem,windows
* Makefile

```makefile
CC = g++
CFLAGS = -c -Wall -Wextra -pedantic -I/mingw64/include
LFLAGS = -L/mingw64/lib -lfreeglut -lopengl32 -lglu32 -lglew32 -Wl,--subsystem,windows
SOURCE = alg.cpp
OBJ = $(SOURCE:.c=.o)
EXE = alg
all: $(SOURCE) $(EXE)
$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf $(OBJ) $(EXE)
```


