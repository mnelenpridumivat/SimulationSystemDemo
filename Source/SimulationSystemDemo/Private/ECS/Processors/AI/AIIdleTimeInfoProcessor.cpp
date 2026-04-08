// Fill out your copyright notice in the Description page of Project Settings.


#include "ECS/Processors/AI/AIIdleTimeInfoProcessor.h"

#include "AIInfoFragment.h"
#include "MassExecutionContext.h"
#include "ECS/Fragments/AI/AIIdleTimeFragment.h"

UAIIdleTimeInfoProcessor::UAIIdleTimeInfoProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (uint8)EProcessorExecutionFlags::Server;
}

void UAIIdleTimeInfoProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FAIInfoFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddTagRequirement<FAIIdleTimeFinishedTag>(EMassFragmentPresence::All);
	EntityQuery.RegisterWithProcessor(*this);
}

void UAIIdleTimeInfoProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	FMassCommandBuffer& CommandBuffer = Context.Defer();
	EntityQuery.ForEachEntityChunk(EntityManager, Context, ([&CommandBuffer](FMassExecutionContext& Context)
	{
		const auto Entities = Context.GetEntities();
		const auto AIInfoFragments = Context.GetMutableFragmentView<FAIInfoFragment>();
		for (int i = 0 ; i < Entities.Num(); ++i)
		{
			auto& Fragment = AIInfoFragments[i];
			Fragment.Facts.Add("Idle");
			CommandBuffer.RemoveTag<FAIIdleTimeFinishedTag>(Entities[i]);
		}
	}));
}
