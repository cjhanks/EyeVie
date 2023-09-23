CXX=g++
CPPFLAGS=
#CXXFLAGS=-O3 -Wall -Wextra -Werror -flto -std=c++14 -g -DNDEBUG -Wno-deprecated-declarations -I/usr/include/eigen3 -IIV
CXXFLAGS=-Wall -O1 -Wextra -Werror -std=c++14 -g -Wno-deprecated-declarations -I/usr/include/eigen3 -IIV
LDFLAGS=-g -lglog

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

# ------------------------------------------------------------------------- #
TESTING_SOURCES = \
	test/CorrelationPoint.cpp \
	test/MetricSpace.cpp \
	test/RunningRegression.cpp \
	test/Voxel.cpp \
	test/Static.cpp \
	test/OccupancyPoint.cpp

TESTING_OBJECTS = $(subst .cpp,.o,$(TESTING_SOURCES))

test: $(TESTING_OBJECTS)
	$(CXX)  -o gtest $(TESTING_OBJECTS) -pthread -lgtest -lgtest_main $(LDFLAGS)

clean:
	$(RM) test/*.o

# ------------------------------------------------------------------------- #
#EXAMPLE_1 = \
#	test/CorrelationPoint.cpp \
#	test/MetricSpace.cpp \
#	test/RunningRegression.cpp \
#	test/Voxel.cpp
#
#TESTING_OBJECTS = $(subst .cpp,.o,$(TESTING_SOURCES))
#
#test: $(TESTING_OBJECTS)
#	$(CXX)  -o gtest $(TESTING_OBJECTS) -pthread -lgtest -lgtest_main $(LDFLAGS)

all: test example
