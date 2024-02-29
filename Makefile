all: world

CXX?=g++
CXXFLAGS?=--std=c++20
LDFLAGS?=-L/usr/lib -L/lib

INCLUDES+= -I./example/include
CXXFLAGS += -Wno-deprecated-declarations -Wno-builtin-declaration-mismatch

OBJS:= \
	objs/podman_signal.o \
	objs/podman_dump.o \
	objs/podman_main.o

PODMAN_DIR:=.
include common/Makefile.inc
include logger/Makefile.inc
include signal/Makefile.inc
include ./Makefile.inc

world: podman

$(shell mkdir -p objs)

objs/podman_dump.o: example/podman_dump.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_signal.o: example/podman_signal.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -I./podman/example -c -o $@ $<;

objs/podman_main.o: example/main.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -I./podman/example -c -o $@ $<;

podman: $(COMMON_OBJS) $(LOGGER_OBJS) $(SIGNAL_OBJS) $(PODMAN_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(LDFLAGS) $(PODMAN_LIBS) $(COMMON_OBJS) $(LOGGER_OBJS) $(PODMAN_OBJS) $(OBJS) -o $@;

clean:
	@rm -rf objs podman
