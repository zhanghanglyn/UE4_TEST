﻿
#include "AssetTypeActions_MyCustomAsset.h"
#include "MyCustomAsset.h"
#include "CustomAssetEditorModule.h"
#define LOCTEXT_NAMESPACE "AssetTypeActions_MyCustomAsset"

FText FAssetTypeActions_MyCustomAsset::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_MyCustomAsset", "AssetTypeActions_MyCustomAsset", "MyCustomAsset");
}

FColor FAssetTypeActions_MyCustomAsset::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FAssetTypeActions_MyCustomAsset::GetSupportedClass() const
{
	return UMyCustomAsset::StaticClass();
}

uint32 FAssetTypeActions_MyCustomAsset::GetCategories()
{
	return EAssetTypeCategories::Sounds;
}

void FAssetTypeActions_MyCustomAsset::OpenAssetEditor(
	const TArray<UObject *>& InObjects,
	TSharedPtr<class IToolkitHost> EditWithinLevelEditor/* = TSharedPtr<IToolkitHost>() */)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for ( auto Object = InObjects.CreateConstIterator(); Object; Object++)
	{
		UMyCustomAsset* CustomAsset = Cast< UMyCustomAsset>(*Object);

		ICustomAssetEditorModule* CustomAssetEditorModuele = &FModuleManager::GetModuleChecked<ICustomAssetEditorModule>("CustomAssetEditor");
		//CustomAssetEditorModuele->CreateCustomAssetEditor(Mode, EditWithinLevelEditor, CustomAsset);
		//TSharedRef<FScenarioEditor> NewEditor = CustomAssetEditorModuele->CreateCustomStoryEditor(Mode, EditWithinLevelEditor, CustomAsset);
		CustomAssetEditorModuele->CreateCustomStoryEditor(Mode, EditWithinLevelEditor, CustomAsset);
	}

}


#undef LOCTEXT_NAMESPACE
