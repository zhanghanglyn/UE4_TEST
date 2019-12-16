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
		�༭�ƶ��ʲ�����
		Param : Mode			    �˱༭�����ʲ��༭ģʽ(������������Ϊ����)
		@param	InitToolkitHost     ��ģʽ������Ϊ����ʱ���������ɲ������ñ༭����LevelEditorʵ��
		@param	InCustomAsset		Ҫ�༭���Զ����ʲ�
	*/
	void InitScenarioEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost>& InitToolkitHost,
		UMyCustomAsset* CustomAsset);



	/* һ�·����̳���FAssetEditorToolkit */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	/* OVER */

	/* ����ʱ���� */
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

	/* ��ǰ���ڱ༭����Դ��MyCustomAsset */
	UMyCustomAsset* CustomAsset;

};