// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Computer/TerminalComputer.h"
#include "UObject/Object.h"
#include "Command.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIVENIGHTSATSOCCYS_API UCommand : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Command")
	void Execute(ATerminalComputer* Computer, UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "Command")
	FString GetCommandName() const { return CommandName; }
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Command", meta = (AllowPrivateAccess = "true"))
	FString CommandName;

	
};
