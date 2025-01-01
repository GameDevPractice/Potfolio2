#include "BTService_Enemy.h"
#include "Character/CEnemy.h"
#include "Character/CPlayer.h"
#include "Component/BehaviorComponent.h"
#include "Component/StateComponent.h"
#include "CAIController.h"


UBTService_Enemy::UBTService_Enemy()
{
	NodeName = TEXT("DefaultEnemy");
}

void UBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	if (AIC == nullptr)
	{
		return;
	}
	UBehaviorComponent* BehaviorComp = Cast<UBehaviorComponent>(AIC->GetComponentByClass(UBehaviorComponent::StaticClass()));

	//Enemy
	ACEnemy* Enemy = Cast<ACEnemy>(AIC->GetPawn());
	if (Enemy == nullptr)
	{
		return;
	}

	UStateComponent* StateComp = Cast<UStateComponent>(Enemy->GetComponentByClass(UStateComponent::StaticClass()));
	if (StateComp->IsHiited())
	{
		BehaviorComp->SetHiitedMode();
		return;
	}

	ACPlayer* Player = BehaviorComp->GetPlayerKey();
	if (Player == nullptr)
	{
		BehaviorComp->SetWaitMode();
		AIC->ClearFocus(EAIFocusPriority::Default);
		return;
	}
	float Distane = Enemy->GetDistanceTo(Player);

	if (Distane < AIC->GetBehaviorRadius())
	{
		AIC->SetFocus(Player);
		BehaviorComp->SetAttackMode();
		return;
	}

	if (Distane < AIC->GetSpecialRadius())
	{
		BehaviorComp->SetSpecialMode();
		return;
	}

	if (Distane < AIC->GetSightRadius())
	{
		BehaviorComp->SetApproachMode();
		return;
	}
	

}
