// Fill out your copyright notice in the Description page of Project Settings.


#include "IsSleepyKnowledgeProcessor.h"

#include "AIInfoFragment.h"
#include "MassExecutionContext.h"
#include "SleepnessFragment.h"

UIsSleepyKnowledgeProcessor::UIsSleepyKnowledgeProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (uint8)EProcessorExecutionFlags::All;
}

void UIsSleepyKnowledgeProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FSleepnessFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FAIInfoFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.RegisterWithProcessor(*this);
}

void UIsSleepyKnowledgeProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const auto HungerFragments = Context.GetFragmentView<FSleepnessFragment>();
		auto KnowledgeFragments = Context.GetMutableFragmentView<FAIInfoFragment>();
		for (int32 i = 0; i < Context.GetNumEntities(); i++)
		{
			if (HungerFragments[i].SleepnessrLevel < 0.5f)
			{
				static FName NewFact = "Sleepy";
				KnowledgeFragments[i].Facts.Add(NewFact);
			}
		}
	});
}
