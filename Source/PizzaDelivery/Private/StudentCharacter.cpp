// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaDelivery/Public/StudentCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AStudentCharacter::AStudentCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStudentCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharMvmt = GetComponentByClass<UCharacterMovementComponent>();
	CharMvmt->MaxWalkSpeed = Speed;

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

bool AStudentCharacter::IsPlayerInRange()
{
	FVector MyLocation = GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();

	float distanceFromPlayer = FVector::Distance(MyLocation, PlayerLocation);

	return distanceFromPlayer <= Range;
}

void AStudentCharacter::ChasePlayer()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsPlayerInRange"), true);
}

void AStudentCharacter::AbandonPlayerChase()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsPlayerInRange"), false);
}

// Called every frame
void AStudentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const bool PlayerInRange = IsPlayerInRange();

	if (PlayerInRange)
	{
		ChasePlayer();
	}
	else if (WasPlayerInRange == true && PlayerInRange == false)
	{
		// Player just left student's range - Wait for x seconds before abandoning the chase
		if (WaitTimerHandle.IsValid())
			GetWorldTimerManager().ClearTimer(WaitTimerHandle);
		
		GetWorldTimerManager().SetTimer(WaitTimerHandle, this, &AStudentCharacter::AbandonPlayerChase,
		                                WaitBeforeAbandoningChase, false);
	}

	WasPlayerInRange = PlayerInRange;
}

// Called to bind functionality to input
void AStudentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

