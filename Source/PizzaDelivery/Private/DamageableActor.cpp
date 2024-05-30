// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableActor.h"


// Sets default values
ADamageableActor::ADamageableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADamageableActor::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

void ADamageableActor::DeactivateInvincibility()
{
	IsInvincible = false;
}

void ADamageableActor::ActivateInvincibility()
{
	IsInvincible = true;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADamageableActor::DeactivateInvincibility,
	                                InvincibilityDuration, false);
}

// Called every frame
void ADamageableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int ADamageableActor::GetHealth()
{
	return Health;
}

void ADamageableActor::TakeDamage(int Damage)
{
	if (IsInvincible)
		return;
	
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
	OnDamaged();

	if (Health <= 0)
		OnDeath();
}

