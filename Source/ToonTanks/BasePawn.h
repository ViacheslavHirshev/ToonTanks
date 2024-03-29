// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent_;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh_;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh_;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint_;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* DeathSound;
};
