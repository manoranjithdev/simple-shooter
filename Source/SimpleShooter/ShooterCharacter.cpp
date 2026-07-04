// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterPlayerController.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AShooterCharacter::OnDamageTaken);

	Health = MaxHealth;
	UpdateHUD();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if(Gun)
	{
		Gun->SetOwner(this);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

		Gun->OwnerController = GetController();
	}
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);

}

void AShooterCharacter::Shoot()
{
	//Pull the trigger
	if(Gun)
	{
		Gun->PullTrigger();
	}
}

void AShooterCharacter::UpdateHUD()
{
	ASimpleShooterPlayerController* PlayerController = Cast<ASimpleShooterPlayerController>(GetController());
	if(PlayerController)
	{
		// percent is btw 0 and 1
		//we have max health and current health 	
		float NewPercent = Health / MaxHealth;	
		if(NewPercent < 0)
		{
			NewPercent = 0;
		}
		PlayerController->HUDWidget->SetHealthBarPercent(NewPercent);
	}
}

void AShooterCharacter::OnDamageTaken(AActor* DamagedActor, float Damage,
		 const UDamageType* DamageType, 
		AController* InstigatedBy, 
		 AActor* DamageCauser)
{
	if(IsAlive)
	{
		Health -= Damage;
		UpdateHUD();
		if (Health <= 0)
		{
			IsAlive = false;
			Health = 0;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			DetachFromControllerPendingDestroy();
		}
	}

	
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}