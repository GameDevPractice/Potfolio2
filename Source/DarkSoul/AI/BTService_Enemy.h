#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Enemy.generated.h"

UCLASS()
class DARKSOUL_API UBTService_Enemy : public UBTService
{
	GENERATED_BODY()
public:
		UBTService_Enemy();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
