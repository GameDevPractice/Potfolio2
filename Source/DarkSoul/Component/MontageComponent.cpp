#include "MontageComponent.h"
#include "GameFramework/Character.h"

UMontageComponent::UMontageComponent()
{
}


void UMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1,1.0,FColor::Red,FString("No DataTable"));
		return;
	}

	//Save Montage
	TArray<FMontageData*> FromDatasTable;
	DataTable->GetAllRows<FMontageData>("", FromDatasTable);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (const auto& Data : FromDatasTable)
		{
			if ((EStateType)i == Data->StateType)
			{
				MontageData[i] = Data;
				break;
			}
		}
	}
	
}

void UMontageComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UMontageComponent::PlayStun()
{
	PlayAnimMontage(EStateType::Stun);
}

void UMontageComponent::PlayAnimMontage(EStateType NewType)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr)
	{
		return;
	}
	const FMontageData* Data = MontageData[(int32)NewType];
	if (Data && Data->AnimMontage)
	{
		Character->PlayAnimMontage(Data->AnimMontage, Data->PlayRate, Data->StartSection);
	}
}


