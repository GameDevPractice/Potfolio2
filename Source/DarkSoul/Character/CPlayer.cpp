#include "CPlayer.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Component/MontageComponent.h"
#include "Component/CActionComponent.h"
#include "Component/CAttributeComponent.h"
#include "Components/BoxComponent.h"


ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMesh* MeshComp;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Character/Meshes/Wukong"));
	if (MeshAsset.Succeeded())
	{
		MeshComp = MeshAsset.Object;
		GetMesh()->SetSkeletalMesh(MeshComp);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f,0.0f,-88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));


	//Components
	StateComp = CreateDefaultSubobject<UStateComponent>(TEXT("StateComp"));
	MontageComp = CreateDefaultSubobject<UMontageComponent>(TEXT("MontageComp"));
	ActionComp = CreateDefaultSubobject<UCActionComponent>(TEXT("ActionComp"));
	AttributeComp = CreateDefaultSubobject<UCAttributeComponent>(TEXT("AttributeComp"));

	//BoxComponent
	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(GetMesh());
	AttackCollision->SetCollisionProfileName("Action");
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	//SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 140.f));
	SpringArmComp->SetRelativeRotation(FRotator(-19.0f, 90.0f, 0.0f));
	SpringArmComp->TargetArmLength = 250.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = false;
	SpringArmComp->ProbeChannel = ECollisionChannel::ECC_Camera;

	//Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	//Player Setting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);



}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	StateComp->OnStateChange.AddDynamic(this, &ACPlayer::OnStateChange);
	AttackCollision->OnComponentBeginOverlap.AddDynamic(ActionComp, &UCActionComponent::OnBeginOverlap);

}



void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ACPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ACPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayer::OnLockUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ACPlayer::OnLockRight);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAction", EInputEvent::IE_Pressed, this, &ACPlayer::PrimaryAction);

}

//FGenericTeamId ACPlayer::GetGenericTeamId() const
//{
//	return FGenericTeamId();
//}



void ACPlayer::Hiited()
{
	MontageComp->PlayHitted();
	//ActionComp->Abort();
	EnableInput(GetController<APlayerController>());
}

void ACPlayer::Stuned()
{
	DisableInput(GetController<APlayerController>());
	MontageComp->PlayStun();
}


void ACPlayer::EndStun()
{
	
	StateComp->SetIdleMode();
	EnableInput(GetController<APlayerController>());
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	//GetCharacterMovement()->MaxWalkSpeed = 600.f;
}


void ACPlayer::MoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetForwardVector();
	AddMovementInput(Direction, Axis);
}

void ACPlayer::MoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRotation).GetRightVector();
	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnLockUp(float Axix)
{
	AddControllerPitchInput(Axix);
}

void ACPlayer::OnLockRight(float Axix)
{
	AddControllerYawInput(Axix);
	
}

void ACPlayer::PrimaryAction()
{
	ActionComp->DoAction();
}

void ACPlayer::OnStateChange(EStateType PreType, EStateType StateType)
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
	case EStateType::Stun:
	{
		Stuned();
	}
	default:
		break;
	}
}