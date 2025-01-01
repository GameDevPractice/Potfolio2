#include "EndAction.h"
#include "Character/CPlayer.h"
#include "Component/CActionComponent.h"

FString UEndAction::GetNotifyName_Implementation() const
{
	return FString("EndAction");
}

void UEndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UCActionComponent* ActionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr)
	{
		return;
	}
	ActionComp->EndAction();
}
