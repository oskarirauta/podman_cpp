#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

#include "common.hpp"
#include "logger.hpp"
#include "podman_t.hpp"
#include "podman_node.hpp"
#include "podman_mutex.hpp"
#include "podman_query.hpp"
#include "podman_container.hpp"

const bool Podman::podman_t::update_stats(void) {

	if ( logger::log_level >= logger::debug.id())
		logger::vverbose << "updating container stats" << std::endl;

	Podman::Query::Response response;
	Podman::Query query = { .group = "containers", .action = "stats", .query = "interval=1",
			.chunks_allowed = 2, .chunks_to_array = true };

	mutex.podman.lock();
	if ( this -> pods.empty()) {
		mutex.podman.unlock();
		return true;
	}

	mutex.podman.unlock();
/*
	if ( this -> state.containers != Podman::Node::OK ) {
		logger::vverbose << "error: failed to update stats, container array not ready" << std::endl;
		return false;
	}
*/

	if ( !this -> socket.execute(query, response)) {
		logger::verbose << "error: socket connection failure" << std::endl;
		return false;
	}

	if ( !json_object_is_type(response.json, json_type_array)) {
		logger::verbose << "failed to call: " << common::trim_leading(query.path()) << std::endl;
		logger::vverbose << "error: json result is not array" << std::endl;
		return false;
	}

	int array_size = json_object_array_length(response.json);
	bool format_err = false;

	if ( array_size < 2 ) {

		logger::vverbose << "error while retrieving stats, incorrect array size" << std::endl;
		return false;
	}

	struct json_object *jvalue = json_object_array_get_idx(response.json, 1);

	if ( struct json_object *jres = json_object_object_get(jvalue, "Error"); json_object_is_type(jres, json_type_string)) {

		logger::vverbose << "error while retrieving stats: " << json_object_get_string(jres) << std::endl;
		return false;
	}

	if ( struct json_object *jres = json_object_object_get(jvalue, "Error"); json_object_is_type(jres, json_type_null)) {

		if ( struct json_object *jarr = json_object_object_get(jvalue, "Stats"); json_object_is_type(jarr, json_type_array)) {

			int arr_size = json_object_array_length(jarr);

			for ( int i2 = 0; i2 < arr_size && !format_err; i2++ ) {

				struct json_object *elem = json_object_array_get_idx(jarr, i2);
				if ( !json_object_is_type(elem, json_type_object)) {
					logger::debug << "stats format error, element is not object" << std::endl;
					format_err = true;
					break;
				}

				std::string containerId;
				int podI = -1;
				int cntrI = -1;

				if ( struct json_object *jval = json_object_object_get(elem, "ContainerID"); json_object_is_type(jval, json_type_string))
					containerId = std::string(json_object_get_string(jval));
				else {
					logger::debug << "stats format error, ContainerId object missing or invalid" << std::endl;
					continue;
					//break;
				}

				if ( containerId.empty()) {
					//format_err = true;
					logger::debug << "stats format error, ContainerId is empty" << std::endl;
					continue;
					//break;
				}

				mutex.podman.lock();
				for ( int _podI = 0; _podI < this -> pods.size() && podI == -1; _podI++ )
					for ( int _cntrI = 0; _cntrI < this -> pods[_podI].containers.size() && cntrI == -1; _cntrI++ )
						if ( this -> pods[_podI].containers[_cntrI].id == containerId ) {
							podI = _podI;
							cntrI = _cntrI;
						}

				if ( podI < 0 || cntrI < 0 ) { // skip stats, not found..
					logger::debug << "stats for container " << containerId << " found, but container not in array; new container?" << std::endl;
					mutex.podman.unlock();
					continue;
				}

				if ( !this -> parse_stats(elem, this -> pods[podI].containers[cntrI]))
					logger::debug << "warning, update stats for container " << this -> pods[podI].containers[cntrI].name << " failed" << std::endl;

				time_t now = std::chrono::duration_cast<std::chrono::seconds>
					(std::chrono::system_clock::now().time_since_epoch()).count();
				this -> pods[podI].containers[cntrI].uptime =
					this -> pods[podI].containers[cntrI].startedAt > 0 ? now - this -> pods[podI].containers[cntrI].startedAt : 0;

				mutex.podman.unlock();
			}

		} else {

			format_err = true;
			logger::debug << "stats format error, Stats array missing or invalid" << std::endl;

		}

	} else format_err = true;

	if ( format_err ) {
		logger::vverbose << "error: format mismatch while getting stats" << std::endl;
		return false;
	}

	mutex.podman.lock();
	this -> state.stats = Podman::Node::OK;
	mutex.podman.unlock();
	return true;
}
