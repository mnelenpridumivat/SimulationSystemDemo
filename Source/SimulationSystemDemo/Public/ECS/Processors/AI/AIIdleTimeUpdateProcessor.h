// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "AIIdleTimeUpdateProcessor.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATIONSYSTEMDEMO_API UAIIdleTimeUpdateProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UAIIdleTimeUpdateProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};
