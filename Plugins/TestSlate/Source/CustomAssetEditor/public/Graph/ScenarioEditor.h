#pragma once

#include "CoreMinimal.h"
#include "Kismet/Public/WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "Runtime/CoreUObject/Public/Misc/NotifyHook.h"
#include "MyCustomAsset.h"
#include "ScenarioGraphEditorSummoner.h"
#include "ScenarioGraph.h"
#include "SWidget.h"
#include "Editor/EditorStyle/Public/EditorStyle.h"
#include "Kismet/Public/BlueprintEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "ScenarioApplicationMode.h"
#include "Kismet/Public/WorkflowOrientedApp/WorkflowTabManager.h"

class FScenarioEditor : public FWorkflowCentricApplication , public FEditorUndoClient ,public FNotifyHook
{
public:

	/*
		�༭�ƶ��ʲ�����
		Param : Mode			    �˱༭�����ʲ��༭ģʽ(������������Ϊ����)
		@param	InitToolkitHost     ��ģʽ������Ϊ����ʱ���������ɲ������ñ༭����LevelEditorʵ��
		@param	InCustomAsset		Ҫ�༭���Զ����ʲ�
	*/
	void InitScenarioEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost>& InitToolkitHost,
		UMyCustomAsset* CustomAsset);

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	/* һ�·����̳���FAssetEditorToolkit */
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

	/* ����ʱ���� */
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
private:
	//��ѡ��ITEM�ı�ʱ����
	virtual void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

private:
	/** Create widget for graph editing */
	TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);

private:
	/**	The tab ids for all the tabs used */
	static const FName PropertiesTabId;

	static const FName ToolkitFName;

	TSharedPtr<FDocumentTracker> DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;

public:
	/* ��ǰ���ڱ༭����Դ��MyCustomAsset */
	UMyCustomAsset* CustomAsset;
	//����ģ��ID
	static const FName ScenarioMode;
};