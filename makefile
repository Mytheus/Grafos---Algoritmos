TARGET = dijkstra
CC = g++
 
CFLAGS  = -Wall


all: $(TARGET)

comp:
			$(CC) $(CFLAGS) -o ./$(TARGET)/$(TARGET).bin ./$(TARGET)/$(TARGET).cpp

exec:
			./$(TARGET)/$(TARGET).bin $(FLAGS)
test:
			$(CC) $(CFLAGS) -o ./Bat1/$(TARGET).bin ./$(TARGET)/$(TARGET).cpp

cleanTest:
			$(RM) ../Bat1/$(TARGET).bin
clean:
			$(RM) ./$(TARGET)/$(TARGET).bin
