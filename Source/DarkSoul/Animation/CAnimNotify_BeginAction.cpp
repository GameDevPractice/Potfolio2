#include "CAnimNotify_BeginAction.h"
#include "Character/CPlayer.h"
#include "Component/CActionComponent.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return FString("BeginAction");
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCActionComponent* ActionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr)
	{
		return;
	}
	ActionComp->BeginAction();
}
