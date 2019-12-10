#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Toolkits/AssetEditorToolkit.h"

class ICustomAssetEditor;
class UMyCustomAsset;

extern const FName CustomAssetEditorAppIdentifier;

class ICustomAssetEditorModule : public IModuleInterface, public IHasMenuExtensibility,
	public IHasToolBarExtensibility
{
public:
	/*
	create a new custom asset editor
	*/
	virtual TSharedRef<ICustomAssetEditor> CreateCustomAssetEditor(
		const EToolkitMode::Type Mode , const TSharedPtr< IToolkitHost>& InitToolkitHost,
		UMyCustomAsset* CustomAsset) = 0;
};

