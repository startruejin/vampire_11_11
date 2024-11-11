// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireVGPlayerController.h"
#include "vampireCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AVampireVGPlayerController::AVampireVGPlayerController()
{

}

void AVampireVGPlayerController::BeginPlay()
{
	controlledCharacter = Cast<AvampireCharacter>(GetPawn());
	if (!controlledCharacter) {
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) 
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AVampireVGPlayerController::OnPossess(APawn* Inpawn)
{
	Super::OnPossess(Inpawn);
	controlledCharacter = Cast<AvampireCharacter>(GetPawn());
}

AvampireCharacter* AVampireVGPlayerController::GetCharacter() {
	if (controlledCharacter == nullptr) {
		controlledCharacter = Cast<AvampireCharacter>(GetPawn());
	}
	return controlledCharacter;
}

void AVampireVGPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(MoveFowardAction, ETriggerEvent::Triggered,this, &AVampireVGPlayerController::MoveFoward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AVampireVGPlayerController::MoveRight);

	}
}

void AVampireVGPlayerController::MoveFoward(const FInputActionValue& value) {
	const float inputValue = value.Get<float>();
	if (GetCharacter() != nullptr) {
		GetCharacter()->AddMovementInput(FVector::ForwardVector, inputValue);
	}
}

void AVampireVGPlayerController::MoveRight(const FInputActionValue& value) {
	const float inputValue = value.Get<float>();
	if (GetCharacter() != nullptr) {
		GetCharacter()->AddMovementInput(FVector::RightVector, inputValue);
	}
}