// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileBody{ nullptr };

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovementComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* ParticleComponent{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound{ nullptr };

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UPROPERTY(EditAnywhere)
	float BaseDamage{ 50.f };

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* HitParticles{ nullptr };

public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
