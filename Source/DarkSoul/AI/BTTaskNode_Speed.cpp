#include "BTTaskNode_Speed.h"
#include "Character/CEnemy.h"
#include "AI/CAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTaskNode_Speed::UBTTaskNode_Speed()
{
	NodeName = TEXT("Speed");
}

EBTNodeResult::Type UBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	if (AIC == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());

	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UCAttributeComponent* Attribute = Cast<UCAttributeComponent>(Enemy->GetComponentByClass(UCAttributeComponent::StaticClass()));
	if (Attribute)
	{
		Attribute->SetWalkSpeed(SpeedType);
		return EBTNodeResult::Succeeded;
	}
	
	
	return EBTNodeResult::Failed;
}
