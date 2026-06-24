# --- Настройки компилятора ---
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# --- Настройка путей для локального vcpkg ---
# Находим все подпапки в vcpkg/installed и исключаем служебную папку 'vcpkg'
VCPKG_ALL_DIRS = $(wildcard vcpkg/installed/*)
VCPKG_TRIPLET_DIR = $(filter-out vcpkg/installed/vcpkg, $(VCPKG_ALL_DIRS))

# Динамически вычисляем пути к заголовочным файлам и библиотекам vcpkg
VCPKG_INCLUDE = $(VCPKG_TRIPLET_DIR)/include
VCPKG_LIB = $(VCPKG_TRIPLET_DIR)/lib

# Добавляем пути импорта для компилятора и линковщика
CXXFLAGS += -I. -IDSL_lib -I$(VCPKG_INCLUDE)
LDFLAGS = -L$(VCPKG_LIB) -ltinyxml2

# Имя итогового исполняемого файла
TARGET = generator

# --- Список исходных файлов проекта ---
SRCS = main.cpp \
       DSL_lib/block_structure/block.cpp \
       DSL_lib/block_structure/utils.cpp \
       DSL_lib/blocks_streaming/blocks_streaming.cpp \
       DSL_lib/code_generation/code_generation.cpp \
       DSL_lib/expressions_building/expressions_building.cpp \
       DSL_lib/expressions_building/utils.cpp \
       DSL_lib/xml_parsing/xml_parser.cpp

# Объектные файлы (.o)
OBJS = $(SRCS:.cpp=.o)

# --- Основные правила ---

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

clean_objs:
	rm -f $(OBJS)

.PHONY: all clean clean_objs