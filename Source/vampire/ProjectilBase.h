// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectilBase.generated.h"



class USkillBaseComponent;
USTRUCT(BlueprintType)
struct FProjectilinfo {

	GENERATED_BODY()


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool penetrate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int hitcount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float initialspeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxspeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gravityScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float lifetime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isexplosion;
};

UCLASS()
class VAMPIRE_API AProjectilBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectilBase();


	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void skillComponent(USkillBaseComponent* newOwnerComponet) { OwnerComponent = newOwnerComponet; }


	UFUNCTION(BlueprintNativeEvent)
	void OnProjectileHit(AActor* otherActor);
	virtual void OnProjectileHit_Implementaion(AActor* otherActor);

	UFUNCTION()
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* collisionSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SphereMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovement;
	int32 hitcount;
	USkillBaseComponent* OwnerComponent;
	UFUNCTION(BlueprintCallable)
	void LaunchProjectile(const FVector& Direction);
	void ApplyDamageToActor(AActor* ActorToDamage);





};