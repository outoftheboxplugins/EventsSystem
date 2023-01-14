// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

EVENTSSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogEventsSystem, Log, All);

#define LOG_TRACE() UE_LOG(LogEventsSystem, Log, TEXT("Trace"))
