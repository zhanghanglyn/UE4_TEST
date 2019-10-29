// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Slate/Public/Widgets/Input/SButton.h"
#include "Modules/ModuleManager.h"
#include "SEventTest.h"
#include "SWidgetTestA.h"
#include "SMyButton.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTestSlateModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	TSharedPtr<SWidgetTestA> m_testWidgetA;
	TSharedPtr<SButton> m_testButton;
};
