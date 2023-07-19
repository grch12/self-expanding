# Customising
PROJECT_NAME = self_expanding
CC           = gcc
LINKER       = gcc
RM           = del /q /f
FLAGS        = -Wall -O3 -D_FILE_OFFSET_BITS=64

C_SOURCES    = $(wildcard *.c)

C_OBJS       = $(patsubst %.c, %.o, $(C_SOURCES))
OBJS         = $(C_OBJS)

EXECUTABLE   = $(PROJECT_NAME).exe

COMPILE_CMD  = $(CC) $^ -o $@ $(FLAGS) -c

.PHONY: everything clean veryclean

everything: $(EXECUTABLE)

clean:
	$(RM) $(OBJS)

veryclean: clean
	$(RM) $(EXECUTABLE)

rebuild: veryclean everything

$(EXECUTABLE): $(OBJS)
	$(LINKER) $^ -o $(EXECUTABLE)

main.o: main.c
	$(COMPILE_CMD)

zip.o: zip.c
	$(COMPILE_CMD)

fileutils.o: fileutils.c
	$(COMPILE_CMD)