// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "ShooterAI.h"


void ASimpleShooterGameMode::BeginPlay()
{
    Super::BeginPlay();

    AShooterCharacter* Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    TArray<AActor*> ShooterAIActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);

    // for (int32 LoopIndex = 0; LoopIndex < ShooterAIActors.Num(); LoopIndex++)
    // {
    //     //AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActors[i]);
        
    //     AActor* ShooterAIActor = ShooterAIActors[LoopIndex];
    //     AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);
    
    //     if(ShooterAI)
    //     {
    //         ShooterAI->StartBehaviorTree(Player);
    //         UE_LOG(LogTemp, Warning, TEXT("Started Behavior Tree for %s"), *ShooterAI->GetActorNameOrLabel());
    //     }
    
    
    // }

    for(AActor* ShooterAIActor : ShooterAIActors)
    {
        AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);
    
        if(ShooterAI)
        {
            ShooterAI->StartBehaviorTree(Player);
            UE_LOG(LogTemp, Warning, TEXT("Started Behavior Tree for %s"), *ShooterAI->GetActorNameOrLabel());
        }
    }

}
