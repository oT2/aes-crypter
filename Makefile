ROOT_DIR =	$(CURDIR)
SRC_DIR =	$(ROOT_DIR)/src
INC_DIR =	$(ROOT_DIR)/include
BIN_DIR = 	$(ROOT_DIR)/bin

CXX =		gcc
CXXFLAGS =	-Wall -Wextra -I$(INC_DIR)
TARGET =	$(BIN_DIR)/aes_crypter.a
SRC =		$(SRC_DIR)/crypter_context.c \
			$(SRC_DIR)/aes_crypter.c
OBJ =		$(SRC:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJ)
	ar ruv $(TARGET) $(OBJ)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all $(TARGET) clean run
