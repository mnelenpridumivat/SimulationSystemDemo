// Fill out your copyright notice in the Description page of Project Settings.


#include "Traits/TestNPCTrait.h"

#include "FoodLocationFragment.h"
#include "MassEntityTemplateRegistry.h"
#include "SleepnessFragment.h"

void UTestNPCTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FHungerFragment>();
	BuildContext.AddFragment<FSleepnessFragment>();
}
