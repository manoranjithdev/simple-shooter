// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	MuzzleFlashParticleSystem->Deactivate();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	MuzzleFlashParticleSystem->Activate(true);

	UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());

	AController* Controller = Cast<AController>(GetOwner()->GetInstigatorController());

	if(Controller){
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		Controller->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);


		FHitResult HitResult;
		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

			bool IsHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ViewPointLocation,
			EndLocation,
				ECollisionChannel::ECC_GameTraceChannel1,
			Params
		);

		if (IsHit)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				ImpactParticleSystem,
				HitResult.ImpactPoint,
				HitResult.ImpactPoint.Rotation()
			);

			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, HitResult.ImpactPoint);

			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, Controller, this, UDamageType::StaticClass());
			}
		}
	}
}

