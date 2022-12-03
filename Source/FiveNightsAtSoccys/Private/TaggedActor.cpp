// Copyright Epic Games, Inc. All Rights Reserved.

#include "TaggedActor.h"

ATaggedActor::ATaggedActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ATaggedActor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AppendTags(StaticGameplayTags);
}

#if WITH_EDITOR
bool ATaggedActor::CanEditChange(const FProperty* InProperty) const
{
	// Prevent editing of the other tags property
	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(AActor, Tags))
	{
		return false;
	}

	return Super::CanEditChange(InProperty);
}

void ATaggedActor::K2_GetOwnedGameplayTags_Implementation(FGameplayTagContainer& TagContainer) const
{
	GetOwnedGameplayTags(TagContainer);
}
#endif
