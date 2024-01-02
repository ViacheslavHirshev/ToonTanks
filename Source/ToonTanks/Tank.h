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

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
