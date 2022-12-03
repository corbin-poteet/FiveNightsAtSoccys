// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"

#include "TaggedActor.generated.h"

// An actor that implements the gameplay tag asset interface
UCLASS()
class ATaggedActor : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:

	ATaggedActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	//~End of IGameplayTagAssetInterface



	
	//~UObject interface
	#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif
	//~End of UObject interface

	protected:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category = "GameplayTags", meta = (DisplayName = "Get Gameplay Tags"))
	void K2_GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const;
	
	// Gameplay-related tags associated with this actor
	UPROPERTY(EditAnywhere, Category=Actor)
	FGameplayTagContainer StaticGameplayTags;
};

