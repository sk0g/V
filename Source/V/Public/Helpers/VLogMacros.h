#pragma once

#define LOG_W(Message) UE_LOG(LogTemp, Warning, TEXT(Message))
#define FLOG_W(Message, ...) UE_LOG(LogTemp, Warning, TEXT(Message), __VA_ARGS__)