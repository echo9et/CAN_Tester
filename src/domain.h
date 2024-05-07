#pragma once

#include <variant>
#include <cstdint>
#include <string>

using Data_t = std::variant<double, uint32_t, int32_t, std::string>;
using DataId_t = uint32_t;

#define JSON_FILE "data.json"
#define NAME_MAIN_LOGGER "all"
#define QUEUE_HMI "/HMI_in_Service_out"
#define CAN_LVL_LOG "CAN"
#define CAN_LISTENER_ID 0

