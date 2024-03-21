# building googletest system 
build_googletest: googletest
	mkdir $@
	cd $@ && cmake ../$< && make && make install

clean_googletest: build_googletest
	rm -rd $<

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC = g++

CFLAGS = -std=c++17 -Wall -Wextra -pthread -lstdc++
ifeq ($(DEBUG),1)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

INCLUDES = \
	include/LongNumber.hpp


CFLAGS += -I $(abspath include)

LDFLAGS=-lgtest -lgmock -lgmock_main -lgtest_main

SOURCESPI = \
  LongNumber.cpp \
	CalculatePi.cpp
 
SOURCESTST = \
  LongNumber.cpp \
	longNumberTest.cpp
 

   
OBJECTSTST = $(SOURCESTST:%.cpp=build/%.o)
OBJECTSPI = $(SOURCESPI:%.cpp=build/%.o)

TEST = build/longNumberTest
EXECPI = build/CalculatePi

default: $(TEST)

$(TEST): $(OBJECTSTST)
	$(CC) $(CFLAGS) $(OBJECTSTST) -o $@ $(LDFLAGS)
 
$(EXECPI): $(OBJECTSPI)
	$(CC) $(CFLAGS) $(OBJECTSPI) -o $@


build/%.o: src/%.cpp $(INCLUDES)
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

test: $(TEST)
	./$(TEST)

pi: $(EXECPI)
	./$(EXECPI)
	

clean:
	rm -rf build

.PHONY: test pi clean default

	
	