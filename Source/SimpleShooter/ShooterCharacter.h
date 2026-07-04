// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	float Health;

	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;

	AGun* Gun;

	void UpdateHUD();

	UFUNCTION()
	void OnDamageTaken(
		 AActor* DamagedActor, float Damage,
		 const class UDamageType* DamageType, 
		 class AController* InstigatedBy, 
		 AActor* DamageCauser 
	);


};
