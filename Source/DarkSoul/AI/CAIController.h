#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class UBehaviorComponent;
class ACEnemy;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class DARKSOUL_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController();

public:
	float GetSightRadius() { return SightRadius; }
	float GetBehaviorRadius() { return BehaviorRadius; }
	float GetSpecialRadius() { return SpecialRaius; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	UFUNCTION()
	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		UBehaviorComponent* BehaviorComp;
	UPROPERTY(VisibleDefaultsOnly)
		UAIPerceptionComponent* PercepComp;

private:
	ACEnemy* OwnerEnemy;
	UAISenseConfig_Sight* SightConfig;

protected:
	UPROPERTY(EditAnywhere)
		float SightRadius;
	UPROPERTY(EditAnywhere)
		float BehaviorRadius;
	UPROPERTY(EditAnywhere)
	float SpecialRaius;
};
