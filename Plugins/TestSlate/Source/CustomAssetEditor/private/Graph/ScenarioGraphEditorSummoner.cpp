#include "ScenarioGraphEditorSummoner.h"
#include "Widgets/Docking/SDockTab.h"

FScenarioGraphEditorSummoner::FScenarioGraphEditorSummoner(TSharedPtr<class FScenarioEditor> ScenarioEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback)
	: FDocumentTabFactoryForObjects<UEdGraph>(TEXT("STory"), ScenarioEditorPtr)
	, ScenarioEditorPtr(ScenarioEditorPtr)
	, OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
}

/* ͨ���ù�������Tab��ʱ�� */
void FScenarioGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(ScenarioEditorPtr.IsValid());
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	//ScenarioEditorPtr.Pin()->OnGraphEditorFocused(GraphEditor);
}

/* ��Ҫˢ��ҳ���ʱ����� */
void FScenarioGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	GraphEditor->NotifyGraphChanged();
}

TAttribute<FText> FScenarioGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* DocumentID) const
{
	return TAttribute<FText>(FText::FromString(DocumentID->GetName()));
}

TSharedRef<SWidget> FScenarioGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FScenarioGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return FEditorStyle::GetBrush("NoBrush");
}
