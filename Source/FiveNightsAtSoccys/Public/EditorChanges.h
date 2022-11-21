// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEdEngine.h"
#include "UObject/Object.h"
#include "EditorChanges.generated.h"

/**
 * 
 */
UCLASS()
class FIVENIGHTSATSOCCYS_API UEditorChanges : public UUnrealEdEngine
{
	GENERATED_BODY()
public:
	virtual void SelectActor(AActor* Actor, bool InSelected, bool bNotify, bool bSelectEvenIfHidden,
		bool bForceRefresh) override;
};
