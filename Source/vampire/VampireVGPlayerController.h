// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "VampireVGPlayerController.generated.h"

class AvampireCharacter;
UCLASS()
class VAMPIRE_API AVampireVGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AVampireVGPlayerController();
	AvampireCharacter* GetCharacter();
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveFowardAction;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveRightAction;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	void MoveFoward(const FInputActionValue& value);
	void MoveRight(const FInputActionValue& value);
	

private:
	class AvampireCharacter* controlledCharacter;
};
