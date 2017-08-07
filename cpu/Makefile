CCFLAGS	:= -O3 -std=c99 -march=native

all: matvec


matvec: matvec.c
	$(CC) $(CCFLAGS) $^ -o $@


matvec.o: matvec.c
	$(CC) $(CCFLAGS) -c $< -o $@


%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $< -o $@


clean:
	@rm -f matvec
	@rm -f *.o


@PHONY: all clean
