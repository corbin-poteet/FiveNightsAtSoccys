// Fill out your copyright notice in the Description page of Project Settings.


#include "Computer/Commands/Command.h"

#include "Computer/TerminalScreen.h"

void UCommand::InitializeCommand(ATerminalComputer* InComputer, UTerminalScreen* InTerminalWidget, UGameplayMessageSubsystem* InGameplayMessageSubsystem)
{
	// Set the computer and terminal widget
	Computer = InComputer;
	TerminalWidget = InTerminalWidget;
	GameplayMessageSubsystem = InGameplayMessageSubsystem;
}

void UCommand::Return(bool bNewLine, bool bSuccess)
{
	TerminalWidget->Return(bNewLine, bSuccess);
}



