#include ../../makefile.inc
#include ../../makefile.local

HDR_FILES := event.hpp \
	iprogram.hpp \
	program_base.hpp \
	runtime.hpp \
	standard_adaptors.hpp \
	standard_functions.hpp \
	statistics.hpp \
	streams.hpp \
	util.hpp
	
SRC_FILES := event.cpp \
	iprogram.cpp \
	program_base.cpp \
	runtime.cpp \
	standard_adaptors.cpp \
	standard_functions.cpp \
	streams.cpp
	
	
FILES := $(HDR_FILES) $(SRC_FILES)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))

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
	
$(OBJ_FILES) : %.o : %.cpp $(HDR_FILES)
	@echo Compiling $<
	@$(G++) -Wall $(CPP_FLAGS) $(patsubst %,-I %,$(CPP_HDR_PATH)) -O3 -c $<

clean: 
	rm -f *.o $(LIB_OBJ)

.PHONY: all clean
