CC = gcc
OUT = Task2
MAKE = Task2

CODE = code
CLASS = Classes
SUBCLASS = SubClasses
NOT_MY = NotMy
BIN = bin
CLEAN_COMMAND = rm -rf $(BIN)/*.o *.o

LIBS = -ldl -lm -lGL -lglfw -lepoxy -lstdc++

BIN_FILES = $(BIN)/main.o $(BIN)/glad.o $(BIN)/stb_image.o $(BIN)/Buffer.o $(BIN)/Color.o $(BIN)/Camera.o $(BIN)/Line.o $(BIN)/Mat.o $(BIN)/Shader.o $(BIN)/Texture.o $(BIN)/GraphRealisation.o $(BIN)/OpenGLRealisation.o

all: $(MAKE)

rebuild: clean all

$(MAKE): $(BIN_FILES)
	$(CC) $(BIN_FILES) $(LIBS) -o "$(OUT)"
	
$(BIN)/main.o:
	$(CC) -c "$(CODE)/main.cpp" -o "$(BIN)/main.o"
	
	
$(BIN)/glad.o:
	$(CC) -c "$(CODE)/$(NOT_MY)/glad.c" -o "$(BIN)/glad.o"
	
$(BIN)/stb_image.o:
	$(CC) -c "$(CODE)/$(NOT_MY)/stb_image.cpp" -o "$(BIN)/stb_image.o"
	
	
$(BIN)/Buffer.o:
	$(CC) -c "$(CODE)/$(CLASS)/Buffer.cpp" -o "$(BIN)/Buffer.o"
	
$(BIN)/Camera.o:
	$(CC) -c "$(CODE)/$(CLASS)/Camera.cpp" -o "$(BIN)/Camera.o"
	
$(BIN)/Color.o:
	$(CC) -c "$(CODE)/$(CLASS)/Color.cpp" -o "$(BIN)/Color.o"
	
$(BIN)/Line.o:
	$(CC) -c "$(CODE)/$(CLASS)/Line.cpp" -o "$(BIN)/Line.o"
	
$(BIN)/Mat.o:
	$(CC) -c "$(CODE)/$(CLASS)/Mat.cpp" -o "$(BIN)/Mat.o"
	
$(BIN)/Shader.o:
	$(CC) -c "$(CODE)/$(CLASS)/Shader.cpp" -o "$(BIN)/Shader.o"
	
$(BIN)/Texture.o:
	$(CC) -c "$(CODE)/$(CLASS)/Texture.cpp" -o "$(BIN)/Texture.o"
	
	
$(BIN)/GraphRealisation.o:
	$(CC) -c "$(CODE)/$(SUBCLASS)/GraphRealisation.cpp" -o "$(BIN)/GraphRealisation.o"
	
$(BIN)/OpenGLRealisation.o:
	$(CC) -c "$(CODE)/$(SUBCLASS)/OpenGLRealisation.cpp" -o "$(BIN)/OpenGLRealisation.o"
	
	
clean:
	$(CLEAN_COMMAND)







