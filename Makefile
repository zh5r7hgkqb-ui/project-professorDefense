CC = gcc
CFLAGS = -Wall -g

SRC = main.c battle.c quiz.c item.c
OBJ = $(SRC:.c=.o)
TARGET = professor_defense

all: $(TARGET)

$(TARGET): $(OBJ)
   $(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
   rm -f $(OBJ) $(TARGET)
