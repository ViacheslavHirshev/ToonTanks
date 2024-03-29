// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent_ = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	BaseMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Base Mesh"));
	TurretMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Turret Mesh"));
	ProjectileSpawnPoint_ = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));

	RootComponent = CapsuleComponent_;
	BaseMesh_->SetupAttachment(CapsuleComponent_);
	TurretMesh_->SetupAttachment(BaseMesh_);
	ProjectileSpawnPoint_->SetupAttachment(TurretMesh_);

}

void ABasePawn::HandleDestruction()
{
	//add visual and sound effects
	if(DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());

	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh_->GetComponentLocation();
	FRotator LookAtRotation(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh_->SetWorldRotation(FMath::RInterpTo(TurretMesh_->GetComponentRotation(), LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 5.f));
}

void ABasePawn::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, 
		ProjectileSpawnPoint_->GetComponentLocation(), ProjectileSpawnPoint_->GetComponentRotation());
	Projectile->SetOwner(this);
}
