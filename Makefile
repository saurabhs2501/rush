CXX := g++
DEBUG_FLAGS := -O0 -g
RELEASE_FLAGS := -O2
CXXFLAGS := -std=c++11 -I src/include -Wall -Wextra

LDFLAGS := -L/usr/lib -L/usr/local/lib
LDLIBS := -lssl -lcrypto

SRC_DIR := src
BLD_DIR := bld
INCLUDE_DIR := src/include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BLD_DIR)/%.o, $(SRCS))
TARGET := $(BLD_DIR)/rushp

all: $(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: all

release: CXXFLAGS += $(RELEASE_FLAGS)
release: all

$(TARGET): $(OBJS)
	@mkdir -p $(BLD_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BLD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BLD_DIR)

rebuild: clean all

.PHONY: all clean rebuild
