#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviorComponent.generated.h"

class UBlackboardComponent;
class ACPlayer;

UENUM(BlueprintType)
enum class FBehaviorType : uint8
{
	Hiited,Wait,Attack,Special ,Approach,Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKSOUL_API UBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBehaviorComponent();

public:
	void SetBlackBoard(UBlackboardComponent* InBlackBoardComp);

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void SetAttackMode();
	UFUNCTION(BlueprintCallable)
	void SetSpecialMode();
	UFUNCTION(BlueprintCallable)
	void SetHiitedMode();
	UFUNCTION(BlueprintCallable)
	void SetApproachMode();
	UFUNCTION(BlueprintCallable)
	void SetWaitMode();

	bool IsSpecialMode();

	ACPlayer* GetPlayerKey();

	UFUNCTION(BlueprintCallable)
		uint8 GetBehaviorType();

private:
	void ChacngeType(FBehaviorType NewType);

private:
	UPROPERTY( EditDefaultsOnly, Category = "Blackboard")
		FName BehaviorKey;
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
		FName PlayerKey;
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
		FName SpecialKey;

protected:
	UBlackboardComponent* BlackboardComp;


 		
};
