#pragma once

#include "CoreMinimal.h"
#include "Kismet/Public/WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "Runtime/CoreUObject/Public/Misc/NotifyHook.h"
#include "MyCustomAsset.h"
#include "ScenarioGraphEditorSummoner.h"
#include "Kismet/Public/BlueprintEditor.h"
#include "Kismet/Public/WorkflowOrientedApp/WorkflowTabManager.h"

class FScenarioEditor : public FWorkflowCentricApplication, public FNotifyHook
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



	/* 一下方法继承自FAssetEditorToolkit */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	/* OVER */

	/* 创建时调用 */
	void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor) {  };
	/** Restores the Story graph we were editing or creates a new one if none is available */
	void RestoreStoryGraph();


private:
	/** Create widget for graph editing */
	TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);

private:
	/**	The tab ids for all the tabs used */
	static const FName PropertiesTabId;

	static const FName ToolkitFName;

	TSharedPtr<FDocumentTracker> DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;

	/* 当前正在编辑的资源，MyCustomAsset */
	UMyCustomAsset* CustomAsset;

};