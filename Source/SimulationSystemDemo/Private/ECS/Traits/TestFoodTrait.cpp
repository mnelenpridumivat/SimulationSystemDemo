// Fill out your copyright notice in the Description page of Project Settings.


#include "Traits/TestFoodTrait.h"

#include "FoodLocationFragment.h"
#include "MassEntityTemplateRegistry.h"

void UTestFoodTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FFoodLocationFragment>();
}
