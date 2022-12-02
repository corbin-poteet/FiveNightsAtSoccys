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
UCLASS(Abstract, Blueprintable, NotPlaceable)
class FIVENIGHTSATSOCCYS_API UCommand : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief Initializes the command with the given computer.
	 * @param Computer 
	 * @param TerminalWidget 
	 */
	UFUNCTION(BlueprintCallable, Category = "Command")
	void InitializeCommand(ATerminalComputer* Computer, UUserWidget* TerminalWidget);

	/**
	 * @brief Executes the command with the given arguments.
	 * @param Args String array of arguments.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Command")
	void Execute(const TArray<FString>& Args);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Command")
	FString GetCommandName() const { return CommandName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Command")
	FString GetCommandDescription() const { return CommandDescription; }
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Command|Info", meta = (AllowPrivateAccess = "true"))
	FString CommandName;

	UPROPERTY(EditDefaultsOnly, Category = "Command|Info", meta = (AllowPrivateAccess = "true"))
	FString CommandDescription;

	UPROPERTY(BlueprintReadOnly, Category = "Command|References", meta = (AllowPrivateAccess = "true"))
	ATerminalComputer* Computer;

	UPROPERTY(BlueprintReadOnly, Category = "Command|References", meta = (AllowPrivateAccess = "true"))
	UUserWidget* TerminalWidget;

	
};
