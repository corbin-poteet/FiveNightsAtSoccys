// Fill out your copyright notice in the Description page of Project Settings.


#include "Computer/Commands/Command.h"

void UCommand::InitializeCommand(ATerminalComputer* InComputer, UUserWidget* InTerminalWidget, UGameplayMessageSubsystem* InGameplayMessageSubsystem)
{
	// Set the computer and terminal widget
	Computer = InComputer;
	TerminalWidget = InTerminalWidget;
	GameplayMessageSubsystem = InGameplayMessageSubsystem;
}
