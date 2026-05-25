// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Action_FindFood.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATIONSYSTEMDEMO_API UAction_FindFood : public UAction
{
	GENERATED_BODY()

public:
	UAction_FindFood();
	
	virtual void StartAction_Implementation(FGOAPBlackboard& Context) override;
	virtual void ProcessAction_Implementation(FGOAPBlackboard& Context) override;
};
