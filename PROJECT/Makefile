CC = gcc

CFLAGS = -Wall -Wextra

TARGET = fdmanager

SOURCES = main.c file_io.c fd_table.c redirect.c ipc.c monitor.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
