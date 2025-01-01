#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAttributeComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk,Run,Max
};

class ACharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKSOUL_API UCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAttributeComponent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetWalkSpeed() { return SpeedType[(int32)ESpeedType::Walk]; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetRunSpeed() { return SpeedType[(int32)ESpeedType::Run]; }

	void SetWalkSpeed(ESpeedType InWalkSpeed);

	float AnyDamage(bool bSpecial, float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;

private:
	ACharacter* Owner;

	UPROPERTY(EditAnywhere)
	float SpeedType[(int32)ESpeedType::Max];
		
};
