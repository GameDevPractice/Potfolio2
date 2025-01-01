#include "Stunned.h"
#include "Character/CPlayer.h"

FString UStunned::GetNotifyName_Implementation() const
{
	return FString("Stunned");
}

void UStunned::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (Player)
	{
		Player->EndStun();
		return;
	}
}
