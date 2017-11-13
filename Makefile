
## Created by Anjuta

CC = gcc
CFLAGS = -g -Wall
OBJECTS = servocontrol.o servoctl.o matrix.o
INCFLAGS = /usr/include
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = -lm

all: servocontrol test_matrix

test_matrix: test_matrix.o matrix.o
	$(CC) -o test_matrix test_matrix.o matrix.o $(LDFLAGS) $(LIBS)

servocontrol: $(OBJECTS)
	$(CC) -o servocontrol $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
