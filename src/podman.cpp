#include <thread>

#include "logger.hpp"
#include "podman.hpp"

std::string libpod_version_override;
Podman::MutexStore Podman::mutex;

void Podman::init(Podman::podman_t *podman) {

	if ( !podman -> update_system())
		logger::info << "Failed to fetch podman system info\n" << std::endl;
	else {
		logger::debug << "Podman system info fetched" << std::endl;

		if ( !podman -> update_networks())
			logger::info << "Failed to fetch podman networks" << std::endl;
		else
			logger::debug << "Podman networks fetched" << std::endl;

		if ( !podman -> update_containers())
			logger::info << "Failed to fetch podman containers" << std::endl;
		else
			logger::debug << "Containers updated" << std::endl;

		if ( !podman -> update_pods())
			logger::info << "Failed to update pods" << std::endl;
		else
			logger::debug << "Pods updated" << std::endl;

		if ( !podman -> update_stats())
			logger::vverbose << "Failed to fetch podman stats" << std::endl;
		else
			logger::debug << "Container stats updated" << std::endl;

		if ( !podman -> update_logs())
			logger::vverbose << "Failed to fetch podman logs" << std::endl;
		else
			logger::debug << "Container logs retrieved" << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

Podman::podman_t *podman_data;
Podman::Scheduler *podman_scheduler;
