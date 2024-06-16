SRC_DIR :=	src
INC_DIR :=	include
BIN_DIR := 	bin
OBJ_DIR := 	obj

CXX :=		gcc
CXXFLAGS :=	-Wall -Wextra -I$(INC_DIR)
TARGET =	libaes_crypter.a
INTERFACE = aes_crypter.h
SRC 	 :=	$(wildcard $(SRC_DIR)/*.c)
OBJ		 :=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CXXFLAGS_TEST := -Wall -Wextra -lcrypto -I$(BIN_DIR)/$(INC_DIR)
TEST_TARGET 	= aes_test
TEST_DIR		= test
TEST_SRC		= $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ		= $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

$(BIN_DIR)/$(TARGET) : $(OBJ) | $(BIN_DIR)/$(INC_DIR)
	ar rv $@ $^
	cp $(INC_DIR)/$(INTERFACE) $(BIN_DIR)/$(INC_DIR)/$(INTERFACE)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(BIN_DIR):
	mkdir $@

$(BIN_DIR)/$(INC_DIR): | $(BIN_DIR)
	mkdir $(BIN_DIR)/$(INC_DIR)

$(TEST_TARGET): $(BIN_DIR)/$(TEST_TARGET)

$(BIN_DIR)/$(TEST_TARGET): $(BIN_DIR)/$(TARGET) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS_TEST) -o $@ $(TEST_OBJ) -L$(BIN_DIR) -laes_crypter -lcrypto

$(TEST_OBJ): $(OBJ_DIR)/%.o : $(TEST_DIR)/%.c
	echo B
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(BIN_DIR)/$(TARGET) || true
	rm -f $(BIN_DIR)/$(INC_DIR)/$(INTERFACE) || true
	rm -f $(TEST_OBJ) $(BIN_DIR)/$(TEST_TARGET) || true

run: $(TARGET)
	./$(TARGET)

.PHONY: all $(TARGET) clean run
