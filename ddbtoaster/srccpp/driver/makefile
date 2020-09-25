G++ := g++
LIB_OBJ := libdriver.a
TARGET:=$(shell which $(G++) &>/dev/null && echo $(LIB_OBJ) || echo warn)
	
SRC_FILES := event.cpp \
	iprogram.cpp \
	program_base.cpp \
	runtime.cpp \
	standard_adaptors.cpp \
	streams.cpp
	
OBJ_FILES := $(patsubst %.cpp,bin/%.o,$(SRC_FILES))

all: $(TARGET)

warn: $(SRC_FILES)
	@echo 
	@echo "------------------------------------------------------------"
	@echo "Warning: C++ library will not be built: $(G++) not found!"
	@echo "------------------------------------------------------------"
	@echo 
	

$(LIB_OBJ) : $(OBJ_FILES)
	@echo "Linking $@"
	@ar cr $@ $^
	
$(OBJ_FILES) : bin/%.o : %.cpp $(HDR_FILES)
	@mkdir -p ./bin
	@echo Compiling $<
	@$(G++) -Wall -std=c++17 $(CPP_FLAGS) -I ../lib -O3 -o $(patsubst %.cpp,bin/%.o,$<) -c $<

clean: 
	rm -rf bin $(LIB_OBJ)

.PHONY: all clean
