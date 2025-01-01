#include "StateComponent.h"

UStateComponent::UStateComponent()
{
}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UStateComponent::SetIdleMode()
{
	ChangeStateType(EStateType::Idle);
}

void UStateComponent::SetHittedMode()
{
	ChangeStateType(EStateType::Hitted);
}

void UStateComponent::SetDeadMode()
{
	ChangeStateType(EStateType::Dead);
}

void UStateComponent::SetActionMode()
{
	ChangeStateType(EStateType::Action);
}

void UStateComponent::SetStunMode()
{
	ChangeStateType(EStateType::Stun);
}

void UStateComponent::ChangeStateType(EStateType InStateType)
{
	if (OnStateChange.IsBound())
	{
		EStateType PreType = StateType;
		StateType = InStateType;
		OnStateChange.Broadcast(PreType, InStateType);
	}
}


