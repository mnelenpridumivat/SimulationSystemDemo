#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "AIIdleTimeFragment.generated.h"

USTRUCT()
struct FAIIdleTimeFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY()
	float IdleTime;

	UPROPERTY()
	float MaxIdleTime;
};

USTRUCT()
struct FAIIdleTimeFinishedTag : public FMassTag
{
	GENERATED_BODY()
};
