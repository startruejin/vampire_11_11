// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyChar.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDieEvent);

UCLASS()
class VAMPIRE_API AEnemyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyChar();
	UPROPERTY(BluePrintAssignable, category = "Events");
	FOnEnemyDieEvent OnEventDieEvent;
	virtual float TakeDamage(float Damageamount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE void SetTargetPlayer(class AvampireCharacter* newPlayer) {
	Targetplayer = newPlayer;
	};
	void Initalize();

protected:
	UPROPERTY();
	class AvampireCharacter* Targetplayer;
	 UAnimInstance* AnimInstance;
	class AAIController* AIController;

	UPROPERTY(BluePrintReadOnly, Category="states")
	float currentHP;
	bool bIsAlive;
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "states")
	UAnimMontage* DieMontage;
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "states")
	UAnimMontage* HitMontage;
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "states")
	UParticleSystem* HitEffect;
	virtual void Destroyed() override;

private:
	void Onhit();
	void OnDie(class AvampireCharacter* LasttAttacker);
	void PlayHitEffect(const FVector& hitLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
