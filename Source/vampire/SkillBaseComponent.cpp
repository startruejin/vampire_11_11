// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBaseComponent.h"
#include "vampireCharacter.h"

// Sets default values for this component's properties
USkillBaseComponent::USkillBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillBaseComponent::BeginPlay()
{
	Super::BeginPlay();
	currentLevel = 0;
	
}

void USkillBaseComponent::ActiveSkillComponent()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_SkillActive);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SkillActive,this,&USkillBaseComponent::PerformSkillAction,SkillInfo.cooldown,true);
}



void USkillBaseComponent::DeactiveSkillComponent()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_SkillActive);
}

void USkillBaseComponent::skilllevelup()
{
	if (currentLevel < 6) {
		currentLevel++;
	}
}

void USkillBaseComponent::PerformSkillAction()
{
	UE_LOG(LogTemp,Error,TEXT("스킬 발동"));
}


