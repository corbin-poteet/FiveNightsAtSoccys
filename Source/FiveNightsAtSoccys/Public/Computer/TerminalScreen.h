// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "TerminalScreen.generated.h"


class UCommand;
/**
 * 
 */
UCLASS()
class FIVENIGHTSATSOCCYS_API UTerminalScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TerminalScreen")
	void Return(bool bNewLine = true, bool bSuccess = false);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "TerminalScreen")
	void Prompt(UCommand* Command);
	
};
