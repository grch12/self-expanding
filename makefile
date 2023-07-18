# Customising
PROJECT_NAME = zipls
CC           = gcc
LINKER       = gcc
RM           = del /q /f
FLAGS        = -Wall -O3

C_SOURCES    = $(wildcard *.c)

C_OBJS       = $(patsubst %.c, %.o, $(C_SOURCES))
OBJS         = $(C_OBJS) $(CXX_OBJS)

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