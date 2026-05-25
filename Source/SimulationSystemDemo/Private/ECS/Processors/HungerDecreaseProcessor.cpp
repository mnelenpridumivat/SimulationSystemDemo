// Fill out your copyright notice in the Description page of Project Settings.


#include "HungerDecreaseProcessor.h"

#include "FoodLocationFragment.h"
#include "MassExecutionContext.h"

UHungerDecreaseProcessor::UHungerDecreaseProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (uint8)EProcessorExecutionFlags::All;
}

void UHungerDecreaseProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FHungerFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this);
}

void UHungerDecreaseProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const auto Fragments = Context.GetMutableFragmentView<FHungerFragment>();
		auto DT = Context.GetDeltaTimeSeconds();
		for (auto& elem : Fragments)
		{
			elem.HungerLevel -= FMath::Max(elem.HungerDecreaseSpeed * DT, 0.0f);
		}
	});
}
