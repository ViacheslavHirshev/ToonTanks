// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent_ = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	TankBaseMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Base Mesh"));
	TankTurretMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Turret Mesh"));
	ProjectileSpawnPoint_ = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));

	RootComponent = CapsuleComponent_;
	TankBaseMesh_->SetupAttachment(CapsuleComponent_);
	TankTurretMesh_->SetupAttachment(TankBaseMesh_);
	ProjectileSpawnPoint_->SetupAttachment(TankTurretMesh_);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

