// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageableActor.generated.h"

UCLASS(Abstract, Blueprintable)
class PIZZADELIVERY_API ADamageableActor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	int Health;

	UPROPERTY()
	bool IsInvincible = false;

	UFUNCTION()
	void DeactivateInvincibility();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHealth = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InvincibilityDuration = 5;

	UFUNCTION(BlueprintCallable)
	virtual int GetHealth();

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(int Damage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	UFUNCTION(BlueprintCallable)
	void ActivateInvincibility();

	UFUNCTION(BlueprintCallable)
	void FullyHealCharacter();
};
