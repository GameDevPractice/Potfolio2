#include "CAnimNotify_SpecialBeginAction.h"
#include "Character/CPlayer.h"
#include "Component/CActionComponent.h"

FString UCAnimNotify_SpecialBeginAction::GetNotifyName_Implementation() const
{
	return FString("SpecialBeginAction");
}

void UCAnimNotify_SpecialBeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCActionComponent* ActionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr)
	{
		return;
	}
	ActionComp->SpecialBeginAction();
}
