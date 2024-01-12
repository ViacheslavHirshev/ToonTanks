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
	TowersCount = GetTowersCount();
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

int32 AToonTanksGameMode::GetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
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

		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TowersCount;

		if (TowersCount == 0)
		{
			GameOver(true);
			TanksPlayerController->SetPlayerEnabledState(false);
		}
			
	}
}