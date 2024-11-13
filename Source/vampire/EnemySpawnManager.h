// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyChar.h"
#include "EnemyAicontroler.h"
#include "EnemySpawnManager.generated.h"

UCLASS()
class VAMPIRE_API AEnemySpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnManager();

protected:
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void StartSpawnMonster();
	void PauseSpawnMonster();
	void ResumeSpawnMonster();

	UFUNCTION()
	void OnEnemyDieCounter();


private:
	class AvampireCharacter* player;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyChar>EnemyBaseClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyAicontroler>EnemyAiControlerClass;
	int MaxSpawnCounter;
	int CurrentSpawnedCounter;
	int MonsterPerSpwan;
	bool BisSpawning;

	FTimerHandle SpawnTimerHandle;
	void IncreaseSpawnCounter();
	void SpawnEnemy();

	FVector GetRandomLocationOnNavMesh(const FVector& Origin, float radius) const;
};
