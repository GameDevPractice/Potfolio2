#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Component/CAttributeComponent.h"
#include "BTTaskNode_Speed.generated.h"

UCLASS()
class DARKSOUL_API UBTTaskNode_Speed : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Speed();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Speed")
	ESpeedType SpeedType;
};
