HTML_OUT=${PWD}/html

CXX=g++
CPPFLAGS=
CXXFLAGS=-O1 -Wall -Wextra -Werror -std=c++14 -g -DNDEBUG -Wno-deprecated-declarations -I/usr/include/eigen3 -IIV -g -mtune=native -march=native
#CXXFLAGS=-Wall -O1 -Wextra -Werror -std=c++14 -g -Wno-deprecated-declarations -I/usr/include/eigen3 -IIV
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
	test/OccupancyPoint.cpp \
	test/VoxelGrid.cpp

TESTING_OBJECTS = $(subst .cpp,.o,$(TESTING_SOURCES))

test: $(TESTING_OBJECTS)
	$(CXX)  -o gtest $(TESTING_OBJECTS) -pthread -lgtest -lgtest_main $(LDFLAGS)

clean:
	$(RM) test/*.o

# ------------------------------------------------------------------------- #
.ONESHELL:
cppcheck:
	mkdir -p $(HTML_OUT)/cpp
	cppcheck \
		$(JOB_FLAG) \
		--xml \
		--enable=all \
		--std=c++11 \
		--platform=unix64 \
		-i IV \
		-i /usr/include \
		-i /usr/include/eigen3 \
		test \
		2> $(HTML_OUT)/cpp/cppcheck.xml

	tools/cppcheck-htmlreport \
		--title="IV" \
		--file=$(HTML_OUT)/cpp/cppcheck.xml \
		--report-dir=$(HTML_OUT)/cpp



all: test example
