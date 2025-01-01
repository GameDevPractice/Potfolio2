#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Speed = 0.0f;
	Direct = 0.0f;
	bIsAir = false;
	Rotator = FRotator::ZeroRotator;
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character == nullptr)
	{
		return;
	}

	Speed = Character->GetVelocity().Size2D();

	AController* PC = Character->GetController();
	if (PC == nullptr)
	{
		return;
	}

	Direct = CalculateDirection(Character->GetVelocity(),FRotator(0,Character->GetControlRotation().Yaw, 0));

	bIsAir = Character->GetCharacterMovement()->IsFalling();

}
