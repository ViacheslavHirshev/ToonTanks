// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (TanksPlayerController)
	{
		TanksPlayerController->SetPlayerEnabledState(false);

		FTimerDelegate TimerDelegate{ FTimerDelegate::CreateUObject(TanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true) };
		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, StartDelay, false);
	}
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (TanksPlayerController)
		{
			TanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}