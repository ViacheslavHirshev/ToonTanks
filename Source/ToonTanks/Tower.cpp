// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

bool ATower::IsFirePossible()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange;
	}
	else
		return false;
}

void ATower::CheckFireCondition()
{
	if (IsFirePossible())
		Fire();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsFirePossible())
		RotateTurret(Tank->GetActorLocation());
}

