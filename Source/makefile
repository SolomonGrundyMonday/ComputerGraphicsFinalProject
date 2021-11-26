# Final Project, Jeff Colgan
# Most of the structure of this makefile is borrowed from in-class examples.
EXE=final

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
FinalMain.o: FinalMain.cpp CSCIx229.h Cuboid.h Tree.h Shovel.h Axe.h Cabin.h Skybox.h Lantern.h Tent.h Horizon.h GameObject.h Camera.h
fatal.o: fatal.c CSCIx229.h 
errcheck.o: errcheck.c CSCIx229.h
print.o: print.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
loadobj.o: loadobj.c CSCIx229.h
projection.o: projection.c CSCIx229.h
Cuboid.o: Cuboid.cpp Cuboid.h GameObject.h Camera.h CSCIx229.h
Camera.o: Camera.cpp Camera.h CSCIx229.h
Tree.o: Tree.cpp Tree.h GameObject.h Camera.h CSCIx229.h
Shovel.o: Shovel.cpp Shovel.h GameObject.h Camera.h CSCIx229.h
Axe.o: Axe.cpp Axe.h GameObject.h Camera.h CSCIx229.h
Cabin.o: Cabin.cpp Cabin.h GameObject.h Camera.h CSCIx229.h
Skybox.o: Skybox.cpp Skybox.h GameObject.h Camera.h CSCIx229.h
Lantern.o: Lantern.cpp Lantern.h GameObject.h Camera.h CSCIx229.h
Tent.o: Tent.cpp Tent.h GameObject.h Camera.h CSCIx229.h
Horizon.o: Horizon.cpp Horizon.h GameObject.h Camera.h CSCIx229.h

# Create archive
CSCIx229.a:fatal.o errcheck.o print.o loadtexbmp.o loadobj.o projection.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
final:FinalMain.o   Cuboid.o   Camera.o   Tree.o   Shovel.o   Axe.o   Cabin.o   Skybox.o   Lantern.o   Tent.o   Horizon.o   CSCIx229.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
