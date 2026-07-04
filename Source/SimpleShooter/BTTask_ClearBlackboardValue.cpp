// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    //Get Blackboard Component
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    // Clear Value of Selected Blackboard Key
    if(Blackboard)
    {
        Blackboard->ClearValue(GetSelectedBlackboardKey());
    }

    // Return Success or Failure
    return EBTNodeResult::Succeeded;
}
