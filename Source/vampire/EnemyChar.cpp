// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyChar.h"
#include "vampireCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyChar::AEnemyChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
	Tags.Add(FName("Enemy"));
}



void AEnemyChar::Initalize()
{
	bIsAlive = true;
	currentHP = 10;
	AIController = Cast<AAIController>(GetController());
	AnimInstance = GetMesh()->GetAnimInstance();
}



void AEnemyChar::Destroyed()
{
	if (AIController) {
		AIController->Destroy();
	}
}

void AEnemyChar::Onhit()
{
	if (AnimInstance && HitMontage) {
		AnimInstance->Montage_Play(HitMontage);
	}

	FVector HitLocation = GetActorLocation();
	PlayHitEffect(HitLocation);
}

void AEnemyChar::OnDie(AvampireCharacter* LasttAttacker)
{
	if (!bIsAlive) {
		return;
	}
	bIsAlive = false;
	if (AIController) {
		AIController->StopMovement();
		Targetplayer = nullptr;
	}
	if (AnimInstance && DieMontage) {
		AnimInstance->Montage_Play(DieMontage);
	}

	/*if (LasttAttacker != nullptr) {
		this->OnEventDieEvent.AddDynamic(LasttAttacker,&AvampireCharacter::OnEnemyDie_EXPUP);
	}*/

	OnEventDieEvent.Broadcast();
	SetLifeSpan(1.5f);
}

float AEnemyChar::TakeDamage(float Damageamount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (EventInstigator == nullptr) {
		return 0;
	}

	if (DamageCauser == nullptr) {
		return 0;
	}
	if (bIsAlive&&currentHP>0) {
		currentHP -= Damageamount;
		if (currentHP < 0) {
			OnDie(Cast<AvampireCharacter>(DamageCauser));
		}
		else {
			Onhit();
		}
	}

	return Super::TakeDamage(Damageamount,DamageEvent,EventInstigator,DamageCauser);
}

void AEnemyChar::PlayHitEffect(const FVector& hitLocation)
{
	if (HitEffect) {
		UWorld* World = GetWorld();
		if (World) {
			UParticleSystemComponent* PSC = UGameplayStatics::SpawnEmitterAtLocation(World,HitEffect,hitLocation);
			if (PSC) {
				PSC->ActivateSystem();
			}

		}
	}
}

// Called every frame
void AEnemyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Targetplayer) {
		if (AIController==nullptr) {
			AIController = Cast<AAIController>(GetController());
		}
		if (AIController->GetMoveStatus() == EPathFollowingStatus::Idle) {
			AIController->MoveToActor(Targetplayer);
		
		}
	}

}



