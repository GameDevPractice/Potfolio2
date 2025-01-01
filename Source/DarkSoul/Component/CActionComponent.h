#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Components/TimeLineComponent.h"
#include "CActionComponent.generated.h"

class ACPlayer;
class UStateComponent;

USTRUCT(BlueprintType)
struct FActionData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* Animation;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	FVector Collsion;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DARKSOUL_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void DoAction();
	void SpecialDoAction();
	void EndAction();
	void BeginAction();
	void SpecialBeginAction();
	void CanCombo();
	void CantCombo();
	void Abort();
	FORCEINLINE FActionData GetData() { return Datas[ComboCount]; }
	FORCEINLINE FActionData GetSpecialData() { return SpecialDatas[SpecialCount]; }

protected:
	UFUNCTION()
		void SecondAttack(float Vaule);

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Nomal")
	TArray<FActionData> Datas;

	UPROPERTY(EditAnywhere, Category = "Special")
	TArray<FActionData> SpecialDatas;
	ACharacter* Owner;
	ACharacter* Character;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TimeLine")
	UCurveFloat* Curve;

	FTimeline TimeLine;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TimeLine")
	float TimelineLength;

private:
	int32 ComboCount;
	bool bSucces;
	bool bCanCombo;
	bool bSpecial;
	bool bSpecialSucces;
	UStateComponent* StateComp;
	FVector CharLoc;
	int32 SpecialCount;
};