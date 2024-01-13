// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileBody;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	MovementComponent->InitialSpeed = 1200.f;
	MovementComponent->MaxSpeed = 1500.f;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	ParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileBody->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
		
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner && HitParticles)
	{
		UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, MyOwnerInstigator, this, DamageTypeClass);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, this->GetActorLocation(), this->GetActorRotation());
	}

	if(HitSound)
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

	Destroy();
}