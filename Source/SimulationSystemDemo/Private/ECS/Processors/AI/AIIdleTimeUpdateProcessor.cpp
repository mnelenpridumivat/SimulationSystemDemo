// Fill out your copyright notice in the Description page of Project Settings.


#include "ECS/Processors/AI/AIIdleTimeUpdateProcessor.h"

#include "AIInfoFragment.h"
#include "MassExecutionContext.h"
#include "ECS/Fragments/AI/AIIdleTimeFragment.h"

UAIIdleTimeUpdateProcessor::UAIIdleTimeUpdateProcessor()
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (uint8)EProcessorExecutionFlags::Server;
}

void UAIIdleTimeUpdateProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FAIIdleTimeFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddTagRequirement<FAIIdleTimeFinishedTag>(EMassFragmentPresence::None);
	EntityQuery.RegisterWithProcessor(*this);
}

void UAIIdleTimeUpdateProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	FMassCommandBuffer& CommandBuffer = Context.Defer();
	EntityQuery.ForEachEntityChunk(EntityManager, Context, ([&CommandBuffer](FMassExecutionContext& Context)
	{
		const auto AIFragments = Context.GetMutableFragmentView<FAIIdleTimeFragment>();
		for (int i = 0 ; i < AIFragments.Num(); ++i)
		{
			auto& Fragment = AIFragments[i];
			Fragment.IdleTime += Context.GetDeltaTimeSeconds();
			if(Fragment.IdleTime >= Fragment.MaxIdleTime)
			{
				auto Entity = Context.GetEntity(i);
				CommandBuffer.AddTag<FAIIdleTimeFinishedTag>(Entity);
				CommandBuffer.RemoveFragment<FAIIdleTimeFragment>(Entity);
			}
		}
	}));
}
