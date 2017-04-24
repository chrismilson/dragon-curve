NAME = dragon

# Output folder
OUTPUT = ./output

SKETCH_FLAG = --sketch="$(NAME)"
OUTPUT_FLAG = --output="$(OUTPUT)"
RUN_FLAG = --run $(FILENAME)

.PHONY : all clean
all :
	- processing-java $(SKETCH_FLAG) $(OUTPUT_FLAG) $(RUN_FLAG)
	@ rm -rf output

clean :
	rm -rf output
