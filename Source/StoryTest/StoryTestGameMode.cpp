// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "StoryTestGameMode.h"
#include "StoryTestHUD.h"
#include "StoryTestCharacter.h"
#include "StoryTest/Script/StoryPlayerPawn.h"
#include "UObject/ConstructorHelpers.h"

AStoryTestGameMode::AStoryTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/StoryTest/BluePrint/MyStoryPlayerPawn"));
	//直接用类的话，就会没有蓝图的各种设置
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass;

	// use our custom HUD class
	HUDClass = AStoryTestHUD::StaticClass();
}
