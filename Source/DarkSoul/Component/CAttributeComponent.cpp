#include "CAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Component/StateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	Owner = Cast<ACharacter>(GetOwner());

	SpeedType[(int32)ESpeedType::Walk] = 400;
	SpeedType[(int32)ESpeedType::Run] = 600;
}


void UCAttributeComponent::SetWalkSpeed(ESpeedType InWalkSpeed)
{
	UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if (Movement == nullptr)
	{
		return;
	}

	Movement->MaxWalkSpeed = SpeedType[(int32)InWalkSpeed];
}

float UCAttributeComponent::AnyDamage(bool bSpecial, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UStateComponent* StateComp = Cast<UStateComponent>(Owner->GetComponentByClass(UStateComponent::StaticClass()));
	if (StateComp == nullptr)
	{
		return 0.0f;
	}
	if (bSpecial)
	{
		StateComp->SetStunMode();
	}
	else
	{
		StateComp->SetHittedMode();
	}
	Owner->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

// Called when the game starts
void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


