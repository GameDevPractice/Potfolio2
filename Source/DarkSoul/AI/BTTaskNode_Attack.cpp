#include "BTTaskNode_Attack.h"
#include "Character/CEnemy.h"
#include "CAIcontroller.h"
#include "Component/CActionComponent.h"
#include "Component/BehaviorComponent.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	UCActionComponent* ActionComp = Cast<UCActionComponent>(Enemy->GetComponentByClass(UCActionComponent::StaticClass()));
	
	if (ActionComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		UBehaviorComponent* BehaviorComp = Cast<UBehaviorComponent>(AIC->GetComponentByClass(UBehaviorComponent::StaticClass()));
		if(BehaviorComp->GetBehaviorType() == (uint8)FBehaviorType::Special)
		{
			ActionComp->SpecialDoAction();
			return EBTNodeResult::Succeeded;
		}
		ActionComp->DoAction();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
