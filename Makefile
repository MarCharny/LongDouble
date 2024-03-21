# building googletest system 
build_googletest: googletest
	mkdir $@
	cd $@ && cmake ../$< && make && make install

clean_googletest: build_googletest
	rm -rd $<

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC = g++

CFLAGS = -std=c++14 -Wall -Wextra -lgtest -lgtest_main -pthread

ifeq($(DEBUG),1)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

INCLUDES = \
	include/LongNumber.hpp

CFLAGS += -I $(abspath include)

SOURCES = \
	LongNumber.cpp \
	longNumberTest.cpp \
	CalculatePi.cpp
OBJECTS = $(SOURCES:%.cpp=build/%.o)
TEST = build/longNumberTest
EXECPI = build/CalculatePi

default: $(EXECUTABLE)

$(TEST): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
$(EXECPI): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


build/%.o: src/%.cpp $(INCLUDES)
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

test: $(TEST)
	./$(TEST)

pi: #(EXECPI)
	

clean:
	rm -rf build

.PHONY: test pi clean default

	
	