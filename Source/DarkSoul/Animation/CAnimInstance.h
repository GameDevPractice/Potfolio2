#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class DARKSOUL_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float Direct;
	UPROPERTY(BlueprintReadOnly)
		bool bIsAir;
	FRotator Rotator;
};
