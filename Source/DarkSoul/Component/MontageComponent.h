#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/StateComponent.h"
#include "Engine/DataTable.h"
#include "MontageComponent.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EStateType StateType;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate;

	UPROPERTY(EditAnywhere)
	FName StartSection;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKSOUL_API UMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontageComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayHitted();
	void PlayStun();

private:
	void PlayAnimMontage(EStateType NewType);

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* DataTable;

private:
	FMontageData* MontageData[(int32)EStateType::Max];
		
};
