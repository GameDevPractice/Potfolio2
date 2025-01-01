#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"



UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle,Hitted, Dead, Action,Stun ,Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPreType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKSOUL_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsIdle() { return StateType == EStateType::Idle; }
	FORCEINLINE bool IsHiited() { return StateType == EStateType::Hitted; }
	FORCEINLINE bool IsDead() { return StateType == EStateType::Dead; }
	FORCEINLINE bool IsAction() { return StateType == EStateType::Action; }
	FORCEINLINE bool IsStun() { return StateType == EStateType::Stun; }

	UFUNCTION(BlueprintCallable)
	void SetIdleMode();
	UFUNCTION(BlueprintCallable)
	void SetHittedMode();
	UFUNCTION(BlueprintCallable)
	void SetDeadMode();
	UFUNCTION(BlueprintCallable)
	void SetActionMode();
	UFUNCTION(BlueprintCallable)
	void SetStunMode();

private:
	void ChangeStateType(EStateType InStateType);
		
public:
	UPROPERTY(BlueprintAssignable)
	FStateTypeChanged OnStateChange;

protected:
	UPROPERTY(BlueprintReadWrite)
	EStateType StateType;
};
