NAME = dragon

# Output folder
OUTPUT = ./output

SKETCH_FLAG = --sketch="$(NAME)"
OUTPUT_FLAG = --output="$(OUTPUT)"
RUN_FLAG = --run $(FILENAME)

.PHONY : all new clean
all :
	- processing-java $(SKETCH_FLAG) $(OUTPUT_FLAG) $(RUN_FLAG)
	@ rm -rf output

new :
	@ mkdir -p $(NAME)
	@ touch $(NAME)/$(NAME).pde

clean :
	rm -rf output
