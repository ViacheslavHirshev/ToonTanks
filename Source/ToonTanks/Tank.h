// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	bool bIsAlive{ true };

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm_ { nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera_ { nullptr };

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TankSpeed {200.f};

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed{ 60.f };

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController {nullptr};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController();
};
