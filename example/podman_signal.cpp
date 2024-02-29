#include "logger.hpp"
#include "podman_loop.hpp"

std::atomic<bool> shouldExit(false);

static void die_handler(int signum) {

	logger::info << "podman_example: received TERM signal" << std::endl;
	shouldExit = true;

}
