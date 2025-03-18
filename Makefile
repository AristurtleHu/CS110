CFLAGS = -g -std=c11 -Wpedantic -Wall -Wextra -Werror

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
TEST_DIR = test
TEST_BUILD_DIR = $(BUILD_DIR)/test

TARGET = $(BIN_DIR)/leaderboard_cli
TEST_SKIPLIST = $(TEST_BUILD_DIR)/test_skiplist

SKIPLIST_SRC = $(SRC_DIR)/skiplist.c
DICT_SRC = $(SRC_DIR)/dict.c
LEADERBOARD_SRC = $(SRC_DIR)/leaderboard.c
MAIN_SRC = $(SRC_DIR)/main.c
TEST_SKIPLIST_SRC = $(TEST_DIR)/test_skiplist.c

SKIPLIST_OBJ = $(BUILD_DIR)/skiplist.o
DICT_OBJ = $(BUILD_DIR)/dict.o
LEADERBOARD_OBJ = $(BUILD_DIR)/leaderboard.o
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_SKIPLIST_OBJ = $(TEST_BUILD_DIR)/test_skiplist.o

.PHONY: all run clean test_skiplist valgrind

all: $(TARGET)

$(BUILD_DIR) $(BIN_DIR) $(TEST_BUILD_DIR):
	mkdir -p $@

$(TARGET): $(LEADERBOARD_OBJ) $(MAIN_OBJ) $(SKIPLIST_OBJ) $(DICT_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

valgrind: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --track-origins=yes $(TARGET)

test_skiplist: $(TEST_SKIPLIST) | $(TEST_BUILD_DIR)
	$(TEST_SKIPLIST)

$(TEST_SKIPLIST): $(TEST_SKIPLIST_OBJ) $(SKIPLIST_OBJ) | $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_SKIPLIST_OBJ): $(TEST_SKIPLIST_SRC) | $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
