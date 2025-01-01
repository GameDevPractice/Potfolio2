#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAction.generated.h"

UCLASS()
class DARKSOUL_API UEndAction : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	FString GetNotifyName_Implementation() const ;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

};
