// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Level/PlayerWidget.h"

UPlayerWidget::UPlayerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPlayerWidget::UpdateProgressBarPercent(const float Percent) const
{
	FoodProgress->SetPercent(Percent);
}
