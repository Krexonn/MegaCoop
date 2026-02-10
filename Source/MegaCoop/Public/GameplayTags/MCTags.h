#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace MCTags
{
	namespace MCAbilities
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sword)
	}
	
	namespace  Events
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(KillScored);
		
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
		}
	}
}
