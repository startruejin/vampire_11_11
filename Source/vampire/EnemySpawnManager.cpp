// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnManager.h"
#include "vampireCharacter.h"
#include "NavigationSystem.h"


// Sets default values
AEnemySpawnManager::AEnemySpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 3.0f;

}



// Called every frame
void AEnemySpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpawnEnemy();

}

void AEnemySpawnManager::StartSpawnMonster()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController) {
		return;
	}
	player = Cast<AvampireCharacter>(PlayerController->GetPawn());
	if (!player) {
		return;
	}
	MaxSpawnCounter = 50;
	CurrentSpawnedCounter = 0;
	MonsterPerSpwan = 5;
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this,&AEnemySpawnManager::IncreaseSpawnCounter,60.0f,true);
	BisSpawning = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawnManager::PauseSpawnMonster()
{
	BisSpawning = false;
	PrimaryActorTick.bCanEverTick = false;
}


void AEnemySpawnManager::ResumeSpawnMonster()
{
	BisSpawning = true;
	PrimaryActorTick.bCanEverTick = true;
}



void AEnemySpawnManager::OnEnemyDieCounter()
{
	CurrentSpawnedCounter--;

}

void AEnemySpawnManager::IncreaseSpawnCounter()
{
	if (BisSpawning) {
		MonsterPerSpwan++;
	}
}

void AEnemySpawnManager::SpawnEnemy()
{
	if (!BisSpawning) {
		return;
	}
	if (!player) {
		return;
	}

	if (!EnemyBaseClass) {
		return;
	}

	if (!EnemyAiControlerClass) {
		return;
	}

	FVector spawnLocation;

	for (int i = 0; i < MonsterPerSpwan; i++) {
		if (CurrentSpawnedCounter < MaxSpawnCounter) {
			float randomAngle= FMath::RandRange(0.0f, 2.0f * PI);
			float randomDistance = FMath::RandRange(1500.0f,1700.0f);
			float x = randomDistance * FMath::Cos(randomAngle);
			float y = randomDistance * FMath::Sin(randomAngle);
			spawnLocation = player->GetActorLocation() + FVector(x, y, 0.0f);
			spawnLocation = GetRandomLocationOnNavMesh(spawnLocation, 100.0f);
			if (!spawnLocation.IsNearlyZero(0.01f)) {
				AEnemyChar* SpawnEnemy = GetWorld()->SpawnActor<AEnemyChar>(EnemyBaseClass, spawnLocation, FRotator::ZeroRotator);
				if (EnemyAiControlerClass&&SpawnEnemy) {
					AEnemyAicontroler* spawnController = GetWorld()->SpawnActor<AEnemyAicontroler>(EnemyAiControlerClass);
					if (spawnController) {
						spawnController->Possess(SpawnEnemy);
					}
					SpawnEnemy->Initalize();
					SpawnEnemy->SetTargetPlayer(player);
					CurrentSpawnedCounter++;
					SpawnEnemy->OnEventDieEvent.AddDynamic(this,&AEnemySpawnManager::OnEnemyDieCounter);
				}
			}

		}
	
	}
}

FVector AEnemySpawnManager::GetRandomLocationOnNavMesh(const FVector& Origin, float radius) const
{
	UWorld* world = GetWorld();
	if (!world) {
		return FVector::ZeroVector;
	}
	const UNavigationSystemV1* Navsys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(world);
	FNavLocation RandomLocation;
	if (Navsys->GetRandomPointInNavigableRadius(Origin, radius, RandomLocation)) {
		return RandomLocation.Location;
	}
	return FVector();
}

