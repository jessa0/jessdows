.PHONY: all clean

all: all.o
clean:
	rm *.o

all.o: kprintf.o string.o trap.o trap_entry.o asm.o
	$(LD) $(LDFLAGS) -o $@ $^
