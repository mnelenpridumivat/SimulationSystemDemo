// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "AIIdleTimeInfoProcessor.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATIONSYSTEMDEMO_API UAIIdleTimeInfoProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UAIIdleTimeInfoProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};
