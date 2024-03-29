#include "podman_busystat.hpp"
#include "podman_mutex.hpp"
#include "podman_t.hpp"

const bool Podman::podman_t::update_busy_cycles(void) {

	Podman::mutex.podman.lock();

	for ( int podI = 0; podI < this -> pods.size(); podI++ ) {

		for ( int idx = 0; idx < this -> pods[podI].containers.size(); idx++ )
			pods[podI].containers[idx].busyState.cycle();

	}

	Podman::mutex.podman.unlock();
	return true;
}
