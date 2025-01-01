#include "CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Component/BehaviorComponent.h"
#include "Character/CEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Character/CPlayer.h"


ACAIController::ACAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorComponent>("BehaviorComp");
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	PercepComp = CreateDefaultSubobject<UAIPerceptionComponent>("PercepComp");

	SetPerceptionComponent(*PercepComp);

	//Sight_Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.0f;

	PercepComp->ConfigureSense(*SightConfig);
	PercepComp->SetDominantSense(SightConfig->GetSenseImplementation());

	SightRadius = 1500.f;
	SpecialRaius = 1000.f;
	BehaviorRadius = 500.f;
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerEnemy = Cast<ACEnemy>(InPawn);

	SetGenericTeamId(2);
	ensure(OwnerEnemy->GetBehaviorTree());

	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);
	BehaviorComp->SetBlackBoard(Blackboard);
	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());

	PercepComp->OnPerceptionUpdated.AddDynamic(this, &ACAIController::ActorsPerceptionUpdated);
}

void ACAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> PerceivedActors;
	PercepComp->GetCurrentlyPerceivedActors(nullptr, PerceivedActors);

	ACPlayer* Player = nullptr;
	for (const auto& Actor : PerceivedActors)
	{
		Player = Cast<ACPlayer>(Actor);

		if (Player)
		{
			break;
		}
	}
	Blackboard->SetValueAsObject("PlayerKey", Player);
}
