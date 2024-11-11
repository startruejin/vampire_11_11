// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GroundCharacter.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRE_API UGroundCharacter : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Locomotion")
	float MoveSpeed;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltasecond) override;

private:
	class APawn* OwnerPawn;
	class UCharacterMovementComponent* MovementComponent;

	
};
