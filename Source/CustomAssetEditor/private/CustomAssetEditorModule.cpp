#include "CustomAssetEditorModule.h"
#include "Toolkits/IToolkit.h"
#include "ModuleManager.h"
#include "CustomAssetEditor.h"

//const FName CustomAssetEditorAppIdentifier = FName(TEXT("CustomAssetEditorApp")); //自定义资产编辑器应用程序标识符

class FCustomAssetEditorModule : public ICustomAssetEditorModule
{
public:
	FCustomAssetEditorModule() {};

	/* 继承子IModuleInterface的接口 */
	virtual void StartupModule() override {
		MenuExtensibliltyManager = MakeShareable(new FExtensibilityManager);
		ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
	};

	virtual void ShutdownModule() override {
		MenuExtensibliltyManager.Reset();
		MenuExtensibliltyManager.Reset();
	}

	virtual TSharedPtr< FExtensibilityManager> GetMenuExtensibilityManager() override {
		return MenuExtensibliltyManager;
	};

	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override {
		return ToolBarExtensibilityManager;
	};

	/* 创建一个AssetEditor */
	virtual  TSharedRef<ICustomAssetEditor> CreateCustomAssetEditor(
		const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost>& InitToolkitHost,
		UMyCustomAsset* CustomAsset) override
	{
		// Initialize and spawn a new custom asset editor with the provided parameters
		TSharedRef< FCustomAssetEditor > NewCustomAssetEditor(new FCustomAssetEditor());
		NewCustomAssetEditor->InitCustomAssetEditorEditor(Mode, InitToolkitHost, CustomAsset);
		return NewCustomAssetEditor;
	}


protected:
	TSharedPtr< FExtensibilityManager> MenuExtensibliltyManager;
	TSharedPtr< FExtensibilityManager> ToolBarExtensibilityManager;
};

IMPLEMENT_GAME_MODULE(FCustomAssetEditorModule, CustomAssetEditor)