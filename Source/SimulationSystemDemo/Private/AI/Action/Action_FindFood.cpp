// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Action/Action_FindFood.h"

#include "ActionPlan.h"
#include "ActionPlannerOwner.h"
#include "GlobalGraph.h"
#include "GraphPositionFragment.h"
#include "MassEntitySubsystem.h"
#include "SimGraphSubsystem.h"
#include "SimulationFunctionLibrary.h"

UAction_FindFood::UAction_FindFood()
{
	Preconditions.Add("FoundFood", false);
	Effects.Add("FoundFood", true);
}

void UAction_FindFood::StartAction_Implementation(FGOAPBlackboard& Context)
{
	Super::StartAction_Implementation(Context);

	auto Owner = GetOwningObject()->GetEntityOwner();
	FSimVertexID Vertex;
	{
		auto EntitySubsystem = GetWorld()->GetSubsystem<UMassEntitySubsystem>();
		auto& Manager = EntitySubsystem->GetEntityManager();
		auto View = Manager.GetFragmentDataStruct(Owner, FGraphPositionFragment::StaticStruct());
		ensure(View.IsValid());
		Vertex = View.Get<FGraphPositionFragment>().Position;
	}
	
	auto Subsystem = GetWorld()->GetSubsystem<USimGraphSubsystem>();
	auto Query = Subsystem->CreateQuery();
	Query.SetEntity(GetOwningObject()->GetEntityOwner());
	Query.SetMaxDistance(10000);
	Query.SetOnlyClosest(true);
	Query.SetGraphStartPosition(USimulationFunctionLibrary::GetGlobalGraph(GetWorld())->GetVertexByID(Vertex));
	Query.GetOnFinished().BindLambda([this, &Context](FSimGraphSearchQueryResult& Result)
	{
		ensure(Result.result == ESimGraphSearchQueryResult::Success);
		auto& NewKey = Context.Context.Add("Food");
		NewKey.Type = EGOAPBlackboardKeyType::Struct;
		NewKey.Struct.InitializeAs(FMassEntityHandle::StaticStruct(), (uint8*)&Result.Found[0]);
		auto Subsystem = GetWorld()->GetSubsystem<UMassEntitySubsystem>();
		auto& Manager = Subsystem->GetEntityManager();
		Manager.Defer().AddFragment<FGraphTargetPositionFragment>(GetOwningObject()->GetEntityOwner());
		FinishAction();
	});
	
}

void UAction_FindFood::ProcessAction_Implementation(FGOAPBlackboard& Context)
{
	Super::ProcessAction_Implementation(Context);
}
