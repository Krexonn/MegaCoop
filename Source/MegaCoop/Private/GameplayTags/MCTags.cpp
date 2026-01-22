#include "GameplayTags/MCTags.h"

namespace MCTags
{
	namespace MCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "MCTags.MCAbilities.ActivateOnGiven", "Tag for the Abilities that should activate immediately once given")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary,"MCTags.MCAbilities.Primary", "Tag for the Primary Ability")
	}
	namespace  Events
	{

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "MCTags.Events.KillScored", "Tag for the KillScored Ability")
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "MCTags.Events.Enemy.HitReact", "Tag for the HitReact Ability")
		}
	}
}
