// Fill out your copyright notice in the Description page of Project Settings.


#include "IsStarvingKnowledgeProcessor.h"

#include "AIInfoFragment.h"
#include "FoodLocationFragment.h"
#include "MassExecutionContext.h"

UIsStarvingKnowledgeProcessor::UIsStarvingKnowledgeProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (uint8)EProcessorExecutionFlags::All;
}

void UIsStarvingKnowledgeProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FHungerFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FAIInfoFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this);
}

void UIsStarvingKnowledgeProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const auto HungerFragments = Context.GetFragmentView<FHungerFragment>();
		auto KnowledgeFragments = Context.GetMutableFragmentView<FAIInfoFragment>();
		for (int32 i = 0; i < Context.GetNumEntities(); i++)
		{
			if (HungerFragments[i].HungerLevel < 0.5f)
			{
				static FName NewFact = "Starving";
				KnowledgeFragments[i].Facts.Add(NewFact);
			}
		}
	});
}
