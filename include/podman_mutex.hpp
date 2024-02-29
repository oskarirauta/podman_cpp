#pragma once

#include <mutex>

namespace Podman {

	struct MutexStore {

		std::mutex podman;
		std::mutex sched;
		std::mutex sock;
	};

	extern Podman::MutexStore mutex;
}
