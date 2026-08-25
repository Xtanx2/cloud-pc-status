CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lcurl

TARGET = cloud_status

SOURCES = main.c system_info.c cloud.c health.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
