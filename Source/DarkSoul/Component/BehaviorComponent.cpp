#include "BehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CPlayer.h"

UBehaviorComponent::UBehaviorComponent()
{
	BehaviorKey = "BehaviorKey";
	PlayerKey = "PlayerKey";
	SpecialKey = "SpecialKey";
}


void UBehaviorComponent::SetBlackBoard(UBlackboardComponent* InBlackBoardComp)
{
	BlackboardComp = InBlackBoardComp;
}

void UBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBehaviorComponent::SetAttackMode()
{
	ChacngeType(FBehaviorType::Attack);
}

void UBehaviorComponent::SetSpecialMode()
{
	ChacngeType(FBehaviorType::Special);
}

void UBehaviorComponent::SetWaitMode()
{
	ChacngeType(FBehaviorType::Wait);
}

void UBehaviorComponent::SetHiitedMode()
{
	ChacngeType(FBehaviorType::Hiited);
}

void UBehaviorComponent::SetApproachMode()
{
	ChacngeType(FBehaviorType::Approach);
}

void UBehaviorComponent::ChacngeType(FBehaviorType NewType)
{
	BlackboardComp->SetValueAsEnum(BehaviorKey, (uint8)NewType);
}

ACPlayer* UBehaviorComponent::GetPlayerKey()
{
	return Cast<ACPlayer>(BlackboardComp->GetValueAsObject(PlayerKey));
}

uint8 UBehaviorComponent::GetBehaviorType()
{
	return BlackboardComp->GetValueAsEnum(BehaviorKey);
}

bool UBehaviorComponent::IsSpecialMode()
{ return BlackboardComp->GetValueAsEnum(BehaviorKey) == (uint8)FBehaviorType::Special; }
