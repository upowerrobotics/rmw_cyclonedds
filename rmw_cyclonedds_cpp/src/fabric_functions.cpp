// Copyright 2019 ADLINK Technology via Rover Robotics and Dan Rose
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fabric_functions.hpp"

namespace fabric_functions
{
  FabricLogger::FabricLogger(const dds_sample_info_t info_, const rmw_subscription_t *subscription_)
    : info(info_), subscription(subscription_) {}

  void FabricLogger::get_log() {
    auto now = std::chrono::system_clock::now();
    int64_t now_timestamp =
        std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
    int64_t timestamp_diff = now_timestamp - info.source_timestamp;

    std::string log_message = "Topic: " + std::string(subscription->topic_name) +
        ", rmw xmt time ns: " + std::to_string(timestamp_diff) + ". RMWPUB TS: " +
        std::to_string(info.source_timestamp) + ", RMWSUB TS: " + std::to_string(now_timestamp);

    RCUTILS_LOG_DEBUG_NAMED("rmw.cyclone", log_message.c_str());
}
}