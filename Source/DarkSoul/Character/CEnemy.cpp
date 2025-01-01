#include "CEnemy.h"
#include "Component/MontageComponent.h"
#include "Component/CActionComponent.h"
#include "Component/BehaviorComponent.h"
#include "Components/BoxComponent.h"
#include "Component/CAttributeComponent.h"

ACEnemy::ACEnemy()
{
	//Components
	StateComp = CreateDefaultSubobject<UStateComponent>(TEXT("StateComp"));
	MontageComp = CreateDefaultSubobject<UMontageComponent>(TEXT("MontageComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorComponent>(TEXT("BehaviorComp"));
	AttributeComp = CreateDefaultSubobject<UCAttributeComponent>(TEXT("AttributeComp"));
	ActionComp = CreateDefaultSubobject<UCActionComponent>(TEXT("ActionComp"));

	//BoxComponent
	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(GetMesh());
	AttackCollision->SetCollisionProfileName("Action");
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 100.f));

	//Mesh
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	StateComp->OnStateChange.AddDynamic(this, &ACEnemy::OnStateChange);
	AttackCollision->OnComponentBeginOverlap.AddDynamic(ActionComp, &UCActionComponent::OnBeginOverlap);
}



float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	StateComp->SetHittedMode();
	return 0.0f;
}

void ACEnemy::Hiited()
{
	MontageComp->PlayHitted();
}

void ACEnemy::OnStateChange(EStateType PreType, EStateType StateType)
{
	switch (StateType)
	{
	case EStateType::Hitted:
	{
		Hiited();
		break;
	}
	case EStateType::Dead:
		break;
	default:
		break;
	}
}




