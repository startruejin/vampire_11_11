// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGroundCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerPawn = TryGetPawnOwner();
}

void UGroundCharacter::NativeUpdateAnimation(float deltasecond)
{
	Super::NativeUpdateAnimation(deltasecond);
	if (!OwnerPawn) {
		return;
	}

	if (!MovementComponent) {
		MovementComponent = OwnerPawn->FindComponentByClass<UCharacterMovementComponent>();
	}

	if (!MovementComponent) {
		return;
	}
	MoveSpeed = MovementComponent->Velocity.Size();
}
