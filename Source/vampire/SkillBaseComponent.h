// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectilBase.h"
#include "SkillBaseComponent.generated.h"

UENUM(BlueprintType)
enum class ESkillType :uint8 {
		Projectil_Forward,
		Projectil_Around,
		Projectil_RadialShoot,
		Projectil_Target,
		AreaCheck_Circuler,
		AreaCheck_Cross
};

USTRUCT(BlueprintType)
struct FSkillInfo {
	GENERATED_BODY();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ESkillType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString iconPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damageRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int projectilcount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProjectilinfo projectilInfo;



};

UCLASS(Abstract, BluePrintable, ClassGroup=(Custom),meta=(BlueprintSpawnableComponent))
class VAMPIRE_API USkillBaseComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillBaseComponent();

protected:
	

public:	
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ActiveSkillComponent();
	UFUNCTION(BlueprintCallable)
	void DeactiveSkillComponent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSkillinfo(const FSkillInfo& newSkillinfo) { SkillInfo = newSkillinfo; }
	FORCEINLINE const FSkillInfo& GetSkillinfo() { return SkillInfo; }
	void skilllevelup();
	UPROPERTY(editdefaultsonly,BlueprintReadWrite,Category="Skill")
	int32 currentLevel;

	UFUNCTION()
	virtual void PerformSkillAction();
	
	UPROPERTY(editdefaultsonly, BlueprintReadWrite, Category = "Skill")
	FSkillInfo SkillInfo;
		
private:
	FTimerHandle TimerHandle_SkillActive;
};

