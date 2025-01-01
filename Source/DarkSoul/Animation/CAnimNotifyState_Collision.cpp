#include "CAnimNotifyState_Collision.h"
#include "Character/CPlayer.h"
#include "Character/CEnemy.h"
#include "Component/CActionComponent.h"
#include "Components/BoxComponent.h"
#include "Component/BehaviorComponent.h"
#include "AI/CAIController.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementaion() const
{
	return FString("Collision");
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	ACPlayer* Player = Cast<ACPlayer>(Owner);
	if (Player)
	{
		
		UBoxComponent* Box = Player->GetCollision();
		Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		UCActionComponent* ActionComp = Cast<UCActionComponent>(Player->GetComponentByClass(UCActionComponent::StaticClass()));
		FActionData Data = ActionComp->GetData();
		Box->SetBoxExtent(Data.Collsion);
		return;
	}
	ACEnemy* Enemy = Cast<ACEnemy>(Owner);
	if (Enemy)
	{
		
		UBoxComponent* Box = Enemy->GetCollision();
		Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		UCActionComponent* ActionComp = Cast<UCActionComponent>(Enemy->GetComponentByClass(UCActionComponent::StaticClass()));
		FActionData Data = ActionComp->GetData();
		FActionData SpecialData = ActionComp->GetSpecialData();

		ACAIController* AIC = Enemy->GetController<ACAIController>();
		UBehaviorComponent* BehaviorComp = Cast<UBehaviorComponent>(AIC->GetComponentByClass(UBehaviorComponent::StaticClass()));
		if (BehaviorComp->IsSpecialMode())
		{
			Box->SetBoxExtent(SpecialData.Collsion);
			return;
		}
		Box->SetBoxExtent(Data.Collsion);
		return;
	}
	
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner == nullptr)
	{
		return;
	}
	ACPlayer* Player = Cast<ACPlayer>(Owner);
	if (Player )
	{
		UBoxComponent* Box = Player->GetCollision();
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
	ACEnemy* Enemy = Cast<ACEnemy>(Owner);
	if (Enemy)
	{
		UBoxComponent* Box = Enemy->GetCollision();
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return;
	}
	
}
