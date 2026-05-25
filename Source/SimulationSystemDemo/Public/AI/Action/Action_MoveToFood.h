// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Action_MoveToFood.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATIONSYSTEMDEMO_API UAction_MoveToFood : public UAction
{
	GENERATED_BODY()

public:
	UAction_MoveToFood();
	
	virtual void StartAction_Implementation(FGOAPBlackboard& Context) override;
	virtual void ProcessAction_Implementation(FGOAPBlackboard& Context) override;
};
