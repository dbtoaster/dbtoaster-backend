#include ../../makefile.inc
#include ../../makefile.local

ifndef BOOST_INC_DIR
BOOST_INC_DIR := /usr/local/include
endif

ifndef BOOST_LIB_DIR
BOOST_LIB_DIR := /usr/local/lib
endif

HDR_FILES := smhasher/MurmurHash2.hpp \
	hpds/pstring.hpp \
	hpds/KDouble.hpp \
	event.hpp \
	iprogram.hpp \
	program_base.hpp \
	runtime.hpp \
	standard_adaptors.hpp \
	standard_functions.hpp \
	statistics.hpp \
	streams.hpp \
	util.hpp \
	
	
SRC_FILES := smhasher/MurmurHash2.cpp \
	hpds/pstring.cpp \
	hpds/KDouble.cpp \
	event.cpp \
	iprogram.cpp \
	program_base.cpp \
	runtime.cpp \
	standard_adaptors.cpp \
	standard_functions.cpp \
	streams.cpp
	
	
FILES := $(HDR_FILES) $(SRC_FILES)
OBJ_FILES := $(patsubst %.cpp,bin/%.o,$(SRC_FILES))

G++ := g++
LIB_OBJ := libdbtoaster.a
TARGET:=$(shell which $(G++) &>/dev/null && echo $(LIB_OBJ) || echo warn)

all: $(TARGET)

warn: $(FILES)
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
	@mkdir -p ./bin/hpds
	@mkdir -p ./bin/smhasher
	@echo Compiling $<
	@$(G++) -I$(BOOST_INC_DIR) -L$(BOOST_LIB_DIR) -Wall -std=c++11 $(CPP_FLAGS) $(patsubst %,-I %,$(CPP_HDR_PATH)) -O3 -o $(patsubst %.cpp,bin/%.o,$<) -c $<

clean: 
	rm -rf bin $(LIB_OBJ)

.PHONY: all clean
