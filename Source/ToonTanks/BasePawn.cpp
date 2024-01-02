// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

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