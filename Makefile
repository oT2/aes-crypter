SRC_DIR :=	src
INC_DIR :=	include
BIN_DIR := 	bin
OBJ_DIR := 	obj

CXX :=		gcc
CXXFLAGS :=	-Wall -Wextra -I$(INC_DIR)
TARGET =	aes_crypter.a
INTERFACE = aes_crypter.h
SRC 	 :=	$(wildcard $(SRC_DIR)/*.c)
OBJ		 :=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(BIN_DIR)/$(TARGET) : $(OBJ) | $(BIN_DIR)/$(INC_DIR)
	ar rv $@ $^
	cp $(INC_DIR)/$(INTERFACE) $(BIN_DIR)/$(INC_DIR)/$(INTERFACE)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(BIN_DIR):
	mkdir $@

$(BIN_DIR)/$(INC_DIR): $(BIN_DIR)
	mkdir $(BIN_DIR)/$(INC_DIR)

clean:
	rm -f $(OBJ) $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(INC_DIR)/$(INTERFACE)

run: $(TARGET)
	./$(TARGET)

.PHONY: all $(TARGET) clean run
