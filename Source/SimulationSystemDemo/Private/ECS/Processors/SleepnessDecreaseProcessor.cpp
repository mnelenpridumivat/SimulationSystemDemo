// Fill out your copyright notice in the Description page of Project Settings.


#include "SleepnessDecreaseProcessor.h"

#include "MassExecutionContext.h"
#include "SleepnessFragment.h"

USleepnessDecreaseProcessor::USleepnessDecreaseProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (uint8)EProcessorExecutionFlags::All;
}

void USleepnessDecreaseProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FSleepnessFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this);
}

void USleepnessDecreaseProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const auto Fragments = Context.GetMutableFragmentView<FSleepnessFragment>();
		auto DT = Context.GetDeltaTimeSeconds();
		for (auto& elem : Fragments)
		{
			elem.SleepnessrLevel -= FMath::Max(elem.SleepnessDecreaseSpeed * DT, 0.0f);
		}
	});
}
