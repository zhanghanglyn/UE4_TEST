
#include "AssetTypeActions_MyCustomAsset.h"


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
	return EAssetTypeCategories::Misc;
}

void FAssetTypeActions_MyCustomAsset::OpenAssetEditor(
	const TArray<UObject *>& InObjects,
	TSharedPtr<class IToolkitHost> EditWithinLevelEditor/* = TSharedPtr<IToolkitHost>() */)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for ( auto Object = InObjects.CreateConstIterator(); Object; Object++)
	{
		UMyCustomAsset* CustomAsset = Cast< UMyCustomAsset>(*Object);

		FCustomAssetEditorModule CustomAssetEditorModuele = FModuleManager::GetModuleChecked<FCustomAssetEditorModule>("CustomAssetEditor");
		CustomAssetEditorModuele.CreateCustomAssetEditor(Mode, EditWithinLevelEditor, CustomAsset);
	}

}