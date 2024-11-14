// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilBase.h"
#include "SkillBaseComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectilBase::AProjectilBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionSphere"));
	collisionSphere->InitSphereRadius(5.0f);
	collisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = collisionSphere;
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetCollisionProfileName(TEXT("NoCollsion"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShape/Sphere'"));
	if (SphereMeshAsset.Succeeded()) {
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}
	SphereMesh->SetupAttachment(collisionSphere);
	SphereMesh->SetRelativeLocation(FVector::ZeroVector);
	SphereMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent() = RootComponent;
	collsionSphere->OnComponentBeginOverlap.AddDynamic(this,&AProjectileBase::)


}

// Called when the game starts or when spawned
void AProjectilBase::BeginPlay()
{
	Super::BeginPlay();
	LaunchProjectile(GetActorForwardVector());
	
}

// Called every frame
void AProjectilBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectilBase::OnProjectileHit(AActor* otherActor)
{
}

void AProjectilBase::OnProjectileHit_Implementaion(AActor* otherActor)
{
}

void AProjectilBase::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AProjectilBase::LaunchProjectile(const FVector& Direction)
{
	if (!ProjectileMovement) {
		return;
	}

	if (!OwnerComponent) {
		return;
	}
	ProjectileMovement->initialSpeed = OwnerComponent->GetSkillinfo().projectilInfo.initialspeed;
	ProjectileMovement->maxSpeed = OwnerComponent->GetSkillinfo().projectilInfo.maxspeed;
	ProjectileMovement->bRoationFollowsVelocity = true;
	ProjectileMovement->velocity = Direction* OwnerComponent->GetSkillinfo().projectilInfo.initialspeed;
	SetLifeSpan(OwnerComponent->GetSkillinfo().projectilInfo.lifetime);
	hitcount = ownerComponent->GetSkillinfo().projectilInfo.hitcount;
}

void AProjectilBase::ApplyDamageToActor(AActor* ActorToDamage)
{
}

