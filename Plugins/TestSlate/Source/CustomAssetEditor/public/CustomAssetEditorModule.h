#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "IAssetTools.h"
#include "AssetTools/Private/AssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_MyCustomAsset.h"

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

