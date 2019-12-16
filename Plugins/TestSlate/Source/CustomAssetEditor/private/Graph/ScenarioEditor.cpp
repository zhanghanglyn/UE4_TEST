#include "ScenarioEditor.h"

const FName FScenarioEditor::ToolkitFName(TEXT("CustomStoryEditor"));
const FName FScenarioEditor::PropertiesTabId(TEXT("CustomAssetEditor_Story"));

#define LOCTEXT_NAMESPACE "CustomStoryEditor"

FName FScenarioEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FScenarioEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Story Editor");
}

FText FScenarioEditor::GetToolkitName() const
{
	return LOCTEXT("AppLabelToolkit", "Custom Story Editor");
}

FText FScenarioEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Custom Story Editor");
}

FString FScenarioEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase ").ToString();
}

FLinearColor FScenarioEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

void FScenarioEditor::InitScenarioEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMyCustomAsset* CustomAsset)
{
	TSharedPtr<FScenarioEditor> ThisPtr(SharedThis(this));
	if (!DocumentManager.IsValid())
	{
		DocumentManager = MakeShareable(new FDocumentTracker());
		// Creates a new tab manager
		DocumentManager->Initialize(ThisPtr);

		TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FScenarioGraphEditorSummoner(ThisPtr,
			FScenarioGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(this, &FScenarioEditor::CreateGraphEditorWidget)
		));

		// Also store off a reference to the grapheditor factory so we can find all the tabs spawned by it later.
		GraphEditorTabFactoryPtr = GraphEditorFactory;
		DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
	}

}

/* 创建GraphEditor! */
TSharedRef<SGraphEditor> FScenarioEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);
	return SNew(SGraphEditor);

}

/* 加载或者重新创建一个Graph */
void FScenarioEditor::RestoreStoryGraph()
{
	<>(CustomAsset->StoryGraph);
}


#undef LOCTEXT_NAMESPACE