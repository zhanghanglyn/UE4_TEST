#include "CustomAssetEditorModule.h"
#include "Toolkits/IToolkit.h"
#include "ModuleManager.h"
#include "CustomAssetEditor.h"

//const FName CustomAssetEditorAppIdentifier = FName(TEXT("CustomAssetEditorApp")); //�Զ����ʲ��༭��Ӧ�ó����ʶ��

class FCustomAssetEditorModule : public ICustomAssetEditorModule
{
public:
	FCustomAssetEditorModule() {};

	/* �̳���IModuleInterface�Ľӿ� */
	virtual void StartupModule() override {
		MenuExtensibliltyManager = MakeShareable(new FExtensibilityManager);
		ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

		RegisterAssetTypeAction( MakeShareable(new FAssetTypeActions_MyCustomAsset()));

	};

	virtual void ShutdownModule() override {
		MenuExtensibliltyManager.Reset();
		MenuExtensibliltyManager.Reset();

		UnregisterAssetTypeAction();
	}

	virtual TSharedPtr< FExtensibilityManager> GetMenuExtensibilityManager() override {
		return MenuExtensibliltyManager;
	};

	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override {
		return ToolBarExtensibilityManager;
	};

	/* ����һ��AssetEditor */
	virtual  TSharedRef<ICustomAssetEditor> CreateCustomAssetEditor(
		const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost>& InitToolkitHost,
		UMyCustomAsset* CustomAsset) override
	{
		// Initialize and spawn a new custom asset editor with the provided parameters
		TSharedRef< FCustomAssetEditor > NewCustomAssetEditor(new FCustomAssetEditor());
		NewCustomAssetEditor->InitCustomAssetEditorEditor(Mode, InitToolkitHost, CustomAsset);
		return NewCustomAssetEditor;
	}

#pragma optimize("",off)
	//ģ�鱻д��ȥ��ʱ���Ҫ��Assetע���ȥ��
	void RegisterAssetTypeAction(TSharedRef<IAssetTypeActions> Actions);
	
#pragma optimize("",on)

	void UnregisterAssetTypeAction()
	{
		if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
		{
			IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
			for (int32 listCount = 0; listCount < ActionList.Num(); listCount)
			{
				AssetTools.UnregisterAssetTypeActions(ActionList[listCount].ToSharedRef());
			}
		}
		ActionList.Empty();
	}


protected:
	TSharedPtr< FExtensibilityManager> MenuExtensibliltyManager;
	TSharedPtr< FExtensibilityManager> ToolBarExtensibilityManager;

	//��¼���б�ע���AssetTypeActions
	TArray< TSharedPtr<IAssetTypeActions>> ActionList;
};

IMPLEMENT_GAME_MODULE(FCustomAssetEditorModule, CustomAssetEditor)

#pragma optimize("",off)
void FCustomAssetEditorModule::RegisterAssetTypeAction(TSharedRef<IAssetTypeActions> Actions)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(Actions);
	ActionList.Add(Actions);
}
#pragma optimize("",on)