G++ := g++
LIB_OBJ := libdbtoaster.a
TARGET:=$(shell which $(G++) &>/dev/null && echo $(LIB_OBJ) || echo warn)
	
SRC_FILES := hash.cpp \
	smhasher/MurmurHash2.cpp \
	hpds/pstring.cpp \
	hpds/pstringops.cpp \
	hpds/KDouble.cpp \
	standard_functions.cpp	
	
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
	
$(OBJ_FILES) : bin/%.o : %.cpp
	@mkdir -p ./bin
	@mkdir -p ./bin/hpds
	@mkdir -p ./bin/smhasher
	@echo Compiling $<
	@$(G++) -Wall -std=c++11 $(CPP_FLAGS) -I . -O3 -o $(patsubst %.cpp,bin/%.o,$<) -c $<

clean: 
	rm -rf bin $(LIB_OBJ)

.PHONY: all clean
