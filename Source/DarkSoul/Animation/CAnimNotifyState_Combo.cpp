#include "CAnimNotifyState_Combo.h"
#include "GameFramework/Character.h"
#include "Component/CActionComponent.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementaion() const
{
	return FString("Combo");
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
	{
		return;
	}

	UCActionComponent* ActionComp = Cast<UCActionComponent>(Owner->GetComponentByClass(UCActionComponent::StaticClass()));
	ActionComp->CanCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	UCActionComponent* ActionComp = Cast<UCActionComponent>(Owner->GetComponentByClass(UCActionComponent::StaticClass()));
	ActionComp->CantCombo();
}
