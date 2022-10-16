#pragma once

#include "../V.h"

#define LOG(Message) UE_LOG(LogVGame, Log, TEXT(Message))
#define FLOG(Message, ...) UE_LOG(LogVGame, Log, TEXT(Message), __VA_ARGS__)

#define LOG_W(Message) UE_LOG(LogVGame, Warning, TEXT(Message))
#define FLOG_W(Message, ...) UE_LOG(LogVGame, Warning, TEXT(Message), __VA_ARGS__)