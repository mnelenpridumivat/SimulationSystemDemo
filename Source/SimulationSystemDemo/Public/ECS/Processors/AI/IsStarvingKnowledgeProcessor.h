// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "IsStarvingKnowledgeProcessor.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATIONSYSTEMDEMO_API UIsStarvingKnowledgeProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UIsStarvingKnowledgeProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

private:
	FMassEntityQuery EntityQuery;
};
