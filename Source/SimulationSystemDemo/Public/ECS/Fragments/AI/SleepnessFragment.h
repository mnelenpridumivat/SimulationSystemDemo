#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "SleepnessFragment.generated.h"

USTRUCT()
struct FSleepnessFragment : public FMassFragment
{
	GENERATED_BODY()

	float SleepnessrLevel = 1.0f;
	float SleepnessDecreaseSpeed = 0.05f;
};