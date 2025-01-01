#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_BeginAction.generated.h"

UCLASS()
class DARKSOUL_API UCAnimNotify_BeginAction : public UAnimNotify
{
	GENERATED_BODY()
protected:
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};
