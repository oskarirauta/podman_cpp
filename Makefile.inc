PODMAN_DIR?=podman
INCLUDES += -I./$(PODMAN_DIR)/include
PODMAN_LIBS:=-lcurl -ljson-c
PODMAN_OBJS:= \
	objs/podman_query.o objs/podman_socket.o objs/podman_validate.o \
	objs/podman_network.o objs/podman_pod.o objs/podman_container.o \
	objs/podman_cmds.o objs/podman_scheduler.o objs/podman_busystat.o \
	objs/podman_stats.o objs/podman_logs.o \
	objs/podman_parser_container.o objs/podman_parser_stats.o \
	objs/podman_t.o objs/podman.o

#EXTRA_CXXFLAGS:=-Wno-builtin-declaration-mismatch

objs/podman_query.o: src/podman_query.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_socket.o: src/podman_socket.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_validate.o: src/podman_validate.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_network.o: src/podman_network.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_pod.o: src/podman_pod.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_container.o: src/podman_container.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_cmds.o: src/podman_cmds.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_t.o: src/podman_t.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_scheduler.o: src/podman_scheduler.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_busystat.o: src/podman_busystat.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_stats.o: src/podman_stats.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_logs.o: src/podman_logs.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_parser_container.o: src/podman_parser_container.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman_parser_stats.o: src/podman_parser_stats.cpp $(DEPS)
	 $(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/podman.o: src/podman.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(INCLUDES) -c -o $@ $<;
