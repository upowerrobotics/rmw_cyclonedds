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

#ifndef FABRIC_FUNCTION_HPP_
#define FABRIC_FUNCTION_HPP_

#include "dds/dds.h"
#include "rcutils/logging_macros.h"
#include "rmw/types.h"

#include <string>
#include <chrono>

namespace fabric_functions
{

class FabricLogger
{
private:
  const dds_sample_info_t info;
  const rmw_subscription_t *subscription;

public:
  FabricLogger(const dds_sample_info_t info_, const rmw_subscription_t *subscription_);
  void get_log();
};

}  // namespace fabric_functions

#endif  // EXCEPTION_HPP_