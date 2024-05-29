// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StudentCharacter.generated.h"

UCLASS()
class PIZZADELIVERY_API AStudentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStudentCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY() UCharacterMovementComponent* CharMvmt;
	UPROPERTY() bool WasPlayerInRange = false;
	UPROPERTY() APawn* PlayerPawn;
	UPROPERTY() FTimerHandle WaitTimerHandle;

	UFUNCTION() bool IsPlayerInRange();
	UFUNCTION() void ChasePlayer();
	UFUNCTION() void AbandonPlayerChase();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Student")
	float Range = 700;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Student")
	float Speed = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Student")
	float WaitBeforeAbandoningChase = 5;
};
