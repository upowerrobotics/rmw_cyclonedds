// Copyright 2023 U Power Robotics USA, Inc.
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

#ifndef FABRIC_FUNCTIONS_HPP_
#define FABRIC_FUNCTIONS_HPP_

#include <chrono>
#include <string>

#include "dds/dds.h"
#include "rcutils/logging_macros.h"
#include "rmw/types.h"

namespace fabric_functions
{

/**
 * @brief Custom logger function for fabric-specific logging.
 *
 * This function logs information related to received messages from a subscription.
 *
 * @param info_ Pointer to the rmw_message_info_t structure that contains message information.
 * @param subscription_ Pointer to the rmw_subscription_t structure representing the subscription.
 * @param dds_name_ The name of the DDS entity for logging purposes.
 */
void fabric_logger(
  const rmw_message_info_t * info_,
  const rmw_subscription_t * subscription_,
  const std::string dds_name_)
{
  auto now = std::chrono::system_clock::now();
  int64_t now_timestamp =
    std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
  int64_t timestamp_diff = now_timestamp - info_->source_timestamp;

  std::ostringstream log_stream;
  log_stream << "Topic: " << subscription_->topic_name <<
    ", rmw xmt time ns: " << timestamp_diff <<
    ". RMWPUB TS: " << info_->source_timestamp <<
    ", RMWSUB TS: " << now_timestamp;
  
  std::vector<std::string> substrings;
  substrings.reserve(2);
  std::istringstream iss(std::string(subscription_->topic_name));
  std::string token;
  while (std::getline(iss, token, '/')) {
    substrings.push_back(std::move(token));
  }

  RCUTILS_LOG_DEBUG_NAMED((substrings[1] + "." + dds_name_).c_str(), log_stream.str().c_str());
}

}  // namespace fabric_functions

#endif  // FABRIC_FUNCTIONS_HPP_
