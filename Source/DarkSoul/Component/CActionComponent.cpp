#include "CActionComponent.h"
#include "Character/CPlayer.h"
#include "Component/StateComponent.h"
#include "Component/CAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Owner = Cast<ACharacter>(GetOwner());
	ComboCount = 0;
	SpecialCount = 0;
	bSucces = false;
	bCanCombo = false;
	bSpecial = false;
	bSpecialSucces = false;
	CharLoc = FVector::ZeroVector;
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	StateComp = Cast<UStateComponent>(GetOwner()->GetComponentByClass(UStateComponent::StaticClass()));

	if (Curve == nullptr)
	{
		return;
	}
	//지정된 Curve에서 사용할 함수
	FOnTimelineFloat CurveCallback;

	//타임라인이 끝난후 실행 될 함수
	FOnTimelineEvent FinishCallback;

	//Callback 함수에 바인드 할 함수
	CurveCallback.BindUFunction(this, FName("SecondAttack"));

	//타임라인에 Curve와 Callback 함수를 추가
	TimeLine.AddInterpFloat(Curve, CurveCallback);

	//타임라인의 길이를 설정
	TimeLine.SetTimelineLength(1.5f);
}

void UCActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeLine.TickTimeline(DeltaTime);
}


void UCActionComponent::DoAction()
{
	if (Datas.Num() <= 0)
	{
		return;
	}
	if (Owner == nullptr)
	{
		return;
	}
	if (bCanCombo)
	{

		bCanCombo = false;
		bSucces = true;
		return;
	}
	if (!(StateComp -> IsIdle()))
	{
		return;
	}
	bSpecial = false;
	StateComp->SetActionMode();
	Owner->PlayAnimMontage(Datas[0].Animation, Datas[0].PlayRate);
}

void UCActionComponent::SpecialDoAction()
{
	if (SpecialDatas.Num() <= 0)
	{
		return;
	}
	if (!(StateComp->IsIdle()))
	{
		return;
	}
	if (bSpecialSucces)
	{
		SpecialBeginAction();
		return;
	}
	bSpecial = true;
	StateComp->SetActionMode();
	Owner->PlayAnimMontage(SpecialDatas[0].Animation, SpecialDatas[0].PlayRate);
}

void UCActionComponent::BeginAction()
{
	if (bSucces == false)
	{
		return;
	}
	bSucces = false;
	Owner->StopAnimMontage();
	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);
	Owner->PlayAnimMontage(Datas[ComboCount].Animation, Datas[ComboCount].PlayRate);
}

void UCActionComponent::SpecialBeginAction()
{
	if (bSpecialSucces == false)
	{
		return;
	}
	bSpecialSucces = false;
	Owner->StopAnimMontage();
	SpecialCount++;
	Owner->PlayAnimMontage(SpecialDatas[SpecialCount].Animation, SpecialDatas[SpecialCount].PlayRate);
	TimeLine.PlayFromStart();
}

void UCActionComponent::CanCombo()
{
	bCanCombo = true;
}

void UCActionComponent::CantCombo()
{
	bCanCombo = false;
}

void UCActionComponent::Abort()
{
	EndAction();
}

void UCActionComponent::SecondAttack(float Value)
{
	if (Character == nullptr)
	{
		
		return;
	}
	CharLoc = Character->GetActorLocation();
	
	FVector ForceDir = (Owner->GetActorLocation() - CharLoc);
	ForceDir.Normalize();
	Owner->SetActorLocation(FMath::Lerp(Owner->GetActorLocation(), CharLoc + FVector(ForceDir.X * 100, ForceDir.Y * 100, 0.0f), Value));
	bSpecial = false;
}

void UCActionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr || OtherActor == GetOwner())
	{
		return;
	}
	Character = Cast<ACharacter>(OtherActor);
	if (Character == nullptr)
	{
		return;
	}
	UCAttributeComponent* Attribute = Cast<UCAttributeComponent>(Character->GetComponentByClass(UCAttributeComponent::StaticClass()));
	if (Attribute == nullptr)
	{
		return;
	}
	FDamageEvent DamageEvent;
	if (bSpecial)
	{
		FVector ForceDir = (Character->GetActorLocation() - Owner->GetActorLocation());
		ForceDir.Normalize();
		Character->GetCharacterMovement()->AddImpulse(ForceDir * 1000000);
		bSpecialSucces = true;
	}
	
	Attribute->AnyDamage(bSpecial,Datas[ComboCount].Damage, DamageEvent, Owner->GetController(), Owner);
}

void UCActionComponent::EndAction()
{
	Owner->StopAnimMontage();
	ComboCount = 0;
	SpecialCount = 0;
	StateComp->SetIdleMode();
}




