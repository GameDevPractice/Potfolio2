#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/StateComponent.h"
#include "CEnemy.generated.h"

class UMontageComponent;
class UCActionComponent;
class UBehaviorComponent;
class UBehaviorTree;
class UBoxComponent;
class UCAttributeComponent;

UCLASS()
class DARKSOUL_API ACEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
		void OnStateChange(EStateType StateType, EStateType PreType);
private:
	void Hiited();

protected:
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

	FORCEINLINE UBoxComponent* GetCollision() { return AttackCollision; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UStateComponent* StateComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UMontageComponent* MontageComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UCActionComponent* ActionComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBehaviorComponent* BehaviorComp;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UCAttributeComponent* AttributeComp;
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* AttackCollision;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UBehaviorTree* BehaviorTree;
};
