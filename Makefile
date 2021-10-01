CC = gcc
OUT = Task2
MAKE = Task2

CODE = code
CLASS = Classes
SUBCLASS = SubClasses
NOT_MY = NotMy
BIN = bin

LIBS = -ldl -lm -lGL -lglfw -lepoxy -lstdc++

BIN_FILES = main.o glad.o stb_image.o Buffer.o Line.o Mat.o Menu.o Shader.o Texture.o GraphRealisation.o MenuRealisation.o OpenGLRealisation.o


all: $(MAKE)

$(MAKE): $(BIN_FILES)
	$(CC) $(BIN_FILES) $(LIBS) -o "$(BIN)/$(OUT)"
	
main.o:
	$(CC) -c "$(CODE)/main.cpp"
	
	
glad.o:
	$(CC) -c -ldl "$(CODE)/$(NOT_MY)/glad.c"
	
stb_image.o:
	$(CC) -c "$(CODE)/$(NOT_MY)/stb_image.cpp"
	
	
Buffer.o:
	$(CC) -c "$(CODE)/$(CLASS)/Buffer.cpp"
	
Line.o:
	$(CC) -c "$(CODE)/$(CLASS)/Line.cpp"
	
Mat.o:
	$(CC) -c "$(CODE)/$(CLASS)/Mat.cpp"
	
Menu.o:
	$(CC) -c "$(CODE)/$(CLASS)/Menu.cpp"
	
Shader.o:
	$(CC) -c "$(CODE)/$(CLASS)/Shader.cpp"
	
Texture.o:
	$(CC) -c "$(CODE)/$(CLASS)/Texture.cpp"
	
	
GraphRealisation.o:
	$(CC) -c "$(CODE)/$(SUBCLASS)/GraphRealisation.cpp"
	
MenuRealisation.o:
	$(CC) -c "$(CODE)/$(SUBCLASS)/MenuRealisation.cpp"
	
OpenGLRealisation.o:
	$(CC) -c "$(CODE)/$(SUBCLASS)/OpenGLRealisation.cpp"
	
	
clean:
	rm -rf *.o







