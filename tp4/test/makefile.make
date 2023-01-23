CC = gcc
CFLAGS = -Wall -ansi 
OBJFILES = creefichierdot.c
TARGET = tp4

all : $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~