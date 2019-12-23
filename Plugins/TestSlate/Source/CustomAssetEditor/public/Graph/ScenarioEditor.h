#pragma once

#include "CoreMinimal.h"
#include "Kismet/Public/WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "Runtime/CoreUObject/Public/Misc/NotifyHook.h"
#include "MyCustomAsset.h"
#include "ScenarioGraphEditorSummoner.h"
#include "ScenarioGraph.h"
#include "SWidget.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"
#include "Slate/Public/Widgets/Docking/SDockTab.h"
#include "Kismet/Public/BlueprintEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "ScenarioApplicationMode.h"
#include "Editor/PropertyEditor/Public/IDetailsView.h"
#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "Kismet/Public/WorkflowOrientedApp/WorkflowTabManager.h"

class FScenarioEditor : public FWorkflowCentricApplication , public FEditorUndoClient ,public FNotifyHook
{
public:

	/*
		编辑制定资产对象
		Param : Mode			    此编辑器的资产编辑模式(独立或以世界为中心)
		@param	InitToolkitHost     当模式以世界为中心时，这是生成并包含该编辑器的LevelEditor实例
		@param	InCustomAsset		要编辑的自定义资产
	*/
	void InitScenarioEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost>& InitToolkitHost,
		UMyCustomAsset* CustomAsset);

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	/* 一下方法继承自FAssetEditorToolkit */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	/* OVER */

	// @todo This is a hack for now until we reconcile the default toolbar with application modes [duplicated from counterpart in Blueprint Editor]
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);

	/* 创建时调用 */
	void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor) {  };
	/** Restores the Story graph we were editing or creates a new one if none is available */
	void RestoreStoryGraph();

	/**
	 * Get the localized text to display for the specified mode
	 * @param	InMode	The mode to display
	 * @return the localized text representation of the mode
	 */
	static FText GetLocalizedMode(FName InMode);

	UMyCustomAsset* GetCustomAsset() const;
	void SetCustomAsset(UMyCustomAsset* InCustomAsset);

	/* 在TabManaget中注册的，产生Tab的委托函数 */
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);

private:
	//在选择ITEM改变时调用
	virtual void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

private:
	/** Create widget for graph editing */
	TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);

	/*创建内部Widget，Details*/
	void CreateInternalWidgets();
	/* DetailsView更新相关 */
	bool IsPropertyEditable() const;
	/*当发生属性变化时的更新*/
	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);

private:
	/**	The tab ids for all the tabs used */
	static const FName PropertiesTabId;

	static const FName ToolkitFName;

	TSharedPtr<FDocumentTracker> DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;

	/* 属性Details */
	TSharedPtr<class IDetailsView> DetailsView;

public:
	/* 当前正在编辑的资源，MyCustomAsset */
	UMyCustomAsset* CustomAsset;
	//剧情模块ID
	static const FName ScenarioMode;
};