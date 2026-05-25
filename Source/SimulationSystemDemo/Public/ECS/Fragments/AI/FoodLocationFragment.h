#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "FoodLocationFragment.generated.h"

USTRUCT()
struct FFoodLocationFragment : public FMassFragment
{
	GENERATED_BODY()

	FMassEntityHandle Food;
};

USTRUCT()
struct FHungerFragment : public FMassFragment
{
	GENERATED_BODY()

	float HungerLevel = 1.0f;
	float HungerDecreaseSpeed = 0.1f;
};