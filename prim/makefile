
CC = g++
 
CFLAGS  = -Wall
 
# The build target 
TARGET = prim

all: $(TARGET)

$(TARGET): $(TARGET).cpp
			$(CC) $(CFLAGS) -o $(TARGET).bin $(TARGET).cpp

exec:
			./$(TARGET).bin

clean:
			$(RM) $(TARGET).bin