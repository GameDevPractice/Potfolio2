#include "Hitted.h"
#include "Character/CPlayer.h"
#include "Component/StateComponent.h"

FString UHitted::GetNotifyName_Implementation() const
{
	return FString("Hiited");
}

void UHitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr)
	{
		return;
	}
	UStateComponent* StateComp = Cast<UStateComponent>(MeshComp->GetOwner()->GetComponentByClass(UStateComponent::StaticClass()));
	if (StateComp)
	{
	StateComp->SetIdleMode();
	}
}
