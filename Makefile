# Các biến cần thiết
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pthread -g -D_REENTRANT -I/usr/include/SDL2 -Iheader
LDFLAGS = -lSDL2 -lSDL2_mixer -lavformat -lavcodec -lavutil -lswresample -lswscale -lavfilter -pthread -I/usr/include/ffmpeg -I/usr/include/vlc -Iheader/Controller -Iheader/Model -Iheader/View -lvlc
HEADER_DIR = header
SRC_DIR = src
BUILD_DIR = build

# Danh sách các thư mục
MODEL_DIR = $(BUILD_DIR)/Model
CONTROLLER_DIR = $(BUILD_DIR)/Controller
VIEW_DIR = $(BUILD_DIR)/View

# Các file nguồn
MODEL_SOURCES = $(wildcard $(SRC_DIR)/Model/*.cpp)
CONTROLLER_SOURCES = $(wildcard $(SRC_DIR)/Controller/*.cpp)
VIEW_SOURCES = $(wildcard $(SRC_DIR)/View/*.cpp)

# File chính
MAIN_SOURCE = main.cpp

# Các file đối tượng
MODEL_OBJECTS = $(patsubst $(SRC_DIR)/Model/%.cpp,$(MODEL_DIR)/%.o,$(MODEL_SOURCES))
CONTROLLER_OBJECTS = $(patsubst $(SRC_DIR)/Controller/%.cpp,$(CONTROLLER_DIR)/%.o,$(CONTROLLER_SOURCES))
VIEW_OBJECTS = $(patsubst $(SRC_DIR)/View/%.cpp,$(VIEW_DIR)/%.o,$(VIEW_SOURCES))

# File thực thi
EXECUTABLE = $(BUILD_DIR)/main

# Quy tắc chính
all: $(EXECUTABLE)

# Quy tắc để tạo file thực thi
$(EXECUTABLE): $(MODEL_OBJECTS) $(CONTROLLER_OBJECTS) $(VIEW_OBJECTS) $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) -o $@ $(BUILD_DIR)/main.o $(MODEL_OBJECTS) $(CONTROLLER_OBJECTS) $(VIEW_OBJECTS) $(LDFLAGS)

# Quy tắc cho file main
$(BUILD_DIR)/main.o: $(MAIN_SOURCE)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR)/Controller -I $(HEADER_DIR)/Model -I $(HEADER_DIR)/View -c $< -o $@

# Quy tắc cho các đối tượng Model
$(MODEL_DIR)/%.o: $(SRC_DIR)/Model/%.cpp
	@mkdir -p $(MODEL_DIR)
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR)/Model -c $< -o $@

# Quy tắc cho các đối tượng Controller
$(CONTROLLER_DIR)/%.o: $(SRC_DIR)/Controller/%.cpp
	@mkdir -p $(CONTROLLER_DIR)
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR)/Controller -I $(HEADER_DIR)/Model -I $(HEADER_DIR)/View -c $< -o $@

# Quy tắc cho các đối tượng View
$(VIEW_DIR)/%.o: $(SRC_DIR)/View/%.cpp
	@mkdir -p $(VIEW_DIR)
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR)/View -I $(HEADER_DIR)/Model -I $(HEADER_DIR)/Controller -c $< -o $@

# Quy tắc xóa các file đã biên dịch
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

.PHONY: all clean