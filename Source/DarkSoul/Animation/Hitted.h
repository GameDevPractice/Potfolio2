#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Hitted.generated.h"

UCLASS()
class DARKSOUL_API UHitted : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	FString GetNotifyName_Implementation() const ;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

};
