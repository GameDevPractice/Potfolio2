#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/StateComponent.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMontageComponent;
class UCActionComponent;
class UBoxComponent;
class UCAttributeComponent;

UCLASS()
class DARKSOUL_API ACPlayer : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void OnLockUp(float Axix);
	void OnLockRight(float Axix);

private:
	void PrimaryAction();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UBoxComponent* GetCollision() { return AttackCollision; }

	//virtual FGenericTeamId GetGenericTeamId() const override;
	void EndStun();

protected:
	UFUNCTION()
		void OnStateChange(EStateType StateType, EStateType PreType);
private:
		void Hiited();
		void Stuned();

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		USpringArmComponent* SpringArmComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UCameraComponent* CameraComp;
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* AttackCollision;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStateComponent* StateComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UMontageComponent* MontageComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCActionComponent* ActionComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UCAttributeComponent* AttributeComp;

};
