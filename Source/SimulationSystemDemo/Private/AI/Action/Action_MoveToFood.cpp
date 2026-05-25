// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Action/Action_MoveToFood.h"

#include "ActionPlan.h"
#include "GraphPositionFragment.h"
#include "GraphTargetPositionFragment.h"
#include "MassEntitySubsystem.h"
#include "NavHeuristic_DistToDest.h"
#include "SimulationFunctionLibrary.h"

UAction_MoveToFood::UAction_MoveToFood()
{
	Preconditions.Add("FoundFood", true);
	Effects.Add("FoundFood", false);
	Effects.Add("RecentlyAte", true);
}

void UAction_MoveToFood::StartAction_Implementation(FGOAPBlackboard& Context)
{
	Super::StartAction_Implementation(Context);

	auto FoodEntity = Context.Context["Food"].Struct.Get<FMassEntityHandle>();
	auto Subsystem = GetWorld()->GetSubsystem<UMassEntitySubsystem>();
	auto& Manager = Subsystem->GetEntityManager();
	auto& TargetFragment = Manager.GetFragmentDataChecked<FGraphPositionFragment>(FoodEntity);
	auto& StartFragment = Manager.GetFragmentDataChecked<FGraphPositionFragment>(GetOwningObject()->GetEntityOwner());
	auto& WayFragment = Manager.GetFragmentDataChecked<FGraphTargetPositionFragment>(GetOwningObject()->GetEntityOwner());
	WayFragment.Way = USimulationFunctionLibrary::FindWay(GetWorld(), StartFragment.Position, TargetFragment.Position,{NewObject<UNavHeuristic_DistToDest>()}).GetWay();
}

void UAction_MoveToFood::ProcessAction_Implementation(FGOAPBlackboard& Context)
{
	Super::ProcessAction_Implementation(Context);
	auto Subsystem = GetWorld()->GetSubsystem<UMassEntitySubsystem>();
	auto& Manager = Subsystem->GetEntityManager();
	auto& WayFragment = Manager.GetFragmentDataChecked<FGraphTargetPositionFragment>(GetOwningObject()->GetEntityOwner());
	if (WayFragment.CurrentPosition == WayFragment.Way.Num - 1)
	{
		FinishAction();
	}
}
