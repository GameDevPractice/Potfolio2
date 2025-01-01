#include "DarkSoulGameModeBase.h"
#include "Character/CPlayer.h"

ADarkSoulGameModeBase::ADarkSoulGameModeBase()
{
	ConstructorHelpers::FClassFinder<ACharacter> PawnClass(TEXT("/Game/Character/Player/BP_CPlayer"));
	if (PawnClass.Succeeded())
	{
		DefaultPawnClass = PawnClass.Class;
	}
}

