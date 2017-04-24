FILE = dragonCurve

.PHONY : all clean
all :
	$(CC) $(FILE).c -lglut -lGL -lglfw -lGLEW -lGLU -o $(FILE)
	./$(FILE)

clean :
	rm ./$(FILE)
