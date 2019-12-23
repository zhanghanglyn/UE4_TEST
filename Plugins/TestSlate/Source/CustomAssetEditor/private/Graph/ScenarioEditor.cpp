#include "ScenarioEditor.h"

const FName FScenarioEditor::ToolkitFName(TEXT("CustomStoryEditor"));
const FName FScenarioEditor::PropertiesTabId(TEXT("CustomAssetEditor_Story"));

const FName FScenarioEditor::ScenarioMode(TEXT("Scenario"));

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

//设置CustomAsset
void FScenarioEditor::SetCustomAsset(UMyCustomAsset* InCustomAsset)
{
	CustomAsset = InCustomAsset;
}

void FScenarioEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	DocumentManager->SetTabManager(InTabManager);

	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);

	//在这里注册一个details试试
	InTabManager->RegisterTabSpawner(PropertiesTabId,
		FOnSpawnTab::CreateSP(this, &FScenarioEditor::SpawnPropertiesTab)) //注册一个当产生TAB时触发的委托
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FScenarioEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

void FScenarioEditor::InitScenarioEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UMyCustomAsset* InCustomAsset)
{
	SetCustomAsset(InCustomAsset);

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


	// if we are already editing objects, dont try to recreate the editor from scratch but update the list of objects in edition
	// ex: BehaviorTree may want to reuse an editor already opened for its associated Blackboard asset.
	const TArray<UObject*>* EditedObjects = GetObjectsCurrentlyBeingEdited();
	if (EditedObjects == nullptr || EditedObjects->Num() == 0)
	{
		//const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(FTabManager::NewPrimaryArea());
		TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("Standalone_CustomAssetEditor_Layout_v1")
			->AddArea(
				FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
				->Split(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.1f)
					->SetHideTabWell(true)
					->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
				)
				// Split the tab and pass the tab id to the tab spawner
				->Split(
					FTabManager::NewSplitter()
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PropertiesTabId, ETabState::OpenedTab)
					)
				)
				->Split(
					FTabManager::NewSplitter()
					->Split
					(
						FTabManager::NewStack()
						->AddTab(TEXT("ddd"), ETabState::OpenedTab)
					)
				)
			);

		//我觉得，之前就是缺少了这一步！！
		InitAssetEditor(Mode, InitToolkitHost, TEXT("ScenarioEditorTreeEditorApp"), DummyLayout,true,true, InCustomAsset);

		CreateInternalWidgets();

		AddApplicationMode(ScenarioMode, MakeShareable(new FScenarioApplicationMode(SharedThis(this))));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" Scenario: EditdObjects IS Aleady EXIST"));
	}

	SetCurrentMode(ScenarioMode);


}

/* 创建GraphEditor! */
TSharedRef<SGraphEditor> FScenarioEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);
	
	//创建一个点击事件
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FScenarioEditor::OnSelectedNodesChanged);

	// Make title bar
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush(TEXT("Graph.TitleBackground")))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.FillWidth(1.f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ScenarioGraphLabel", "Scenario"))
			.TextStyle(FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
		]
		];
	
	return SNew(SGraphEditor)
		.TitleBar(TitleBarWidget)
		.GraphToEdit(InGraph)
		.GraphEvents(InEvents)
		;

}

TSharedRef<SDockTab> FScenarioEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
			// Provide the details view as this tab its content
			DetailsView.ToSharedRef()
		];
}

/* 加载或者重新创建一个Graph */
void FScenarioEditor::RestoreStoryGraph()
{
	UScenarioGraph* MyGraph = Cast<UScenarioGraph>(CustomAsset->StoryGraph);
	const bool bNewGraph = MyGraph == NULL;
	if (MyGraph == NULL)
	{
		CustomAsset->StoryGraph = FBlueprintEditorUtils::CreateNewGraph(CustomAsset, TEXT("MyScenario Tree"), UScenarioGraph::StaticClass(), UScenarioGraphSchema::StaticClass());
		MyGraph = Cast<UScenarioGraph>(CustomAsset->StoryGraph);
		
		//初始化编辑器的Graph
		const UScenarioGraphSchema* Schema = Cast<UScenarioGraphSchema>(MyGraph->GetSchema());
		Schema->CreateDefaultNodesForGraph(*MyGraph);

	}

	//把MyGraph 做成一个新的有效负载包装,使用OpenDocument创建了一个新的TAB！
	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(MyGraph);
	TSharedPtr<SDockTab> DocumentTab = DocumentManager->OpenDocument(Payload, bNewGraph ? FDocumentTracker::OpenNewDocument : FDocumentTracker::RestorePreviousDocument);

	//关于lastEditedDocuments那段，先不写
	/*
	if(BehaviorTree->LastEditedDocuments.Num() > 0)
	{
		TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(DocumentTab->GetContent());
		GraphEditor->SetViewLocation(BehaviorTree->LastEditedDocuments[0].SavedViewOffset, BehaviorTree->LastEditedDocuments[0].SavedZoomAmount);
	}
	*/
}

void FScenarioEditor::RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

/* 在此创建Details等内部的Widget */
void FScenarioEditor::CreateInternalWidgets()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	//DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
	DetailsViewArgs.NotifyHook = this;
	//创建DetailsView
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject( NULL );
	DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateSP(this, &FScenarioEditor::IsPropertyEditable));
	//设置改Node名Node显示之类的？
	DetailsView->OnFinishedChangingProperties().AddSP(this, &FScenarioEditor::OnFinishedChangingProperties);
}

FText FScenarioEditor::GetLocalizedMode(FName InMode)
{
	static TMap< FName, FText > LocModes;

	if (LocModes.Num() == 0)
	{
		LocModes.Add(ScenarioMode, LOCTEXT("ScenarioMode", "Scenario"));
	}

	check(InMode != NAME_None);
	const FText* OutDesc = LocModes.Find(InMode);
	check(OutDesc);
	return *OutDesc;
}

UMyCustomAsset* FScenarioEditor::GetCustomAsset() const
{
	return CustomAsset;
}

//在选择ITEM改变时调用
void FScenarioEditor::OnSelectedNodesChanged(const TSet<class UObject *>& NewSelection)
{
	//在这里添加点击Item时对DetailsView的改变 , 目前只写对一个Node的操作
	int32 SelectionNodeNum = NewSelection.Num();

	if (DetailsView.IsValid() == true)
	{
		if (SelectionNodeNum == 1)
		{
			for (UObject* Object : NewSelection)
			{
				DetailsView->SetObject(Object);
			}
		}
		else
		{
			DetailsView->SetObject(NULL);
		}
		
	}	
}

bool FScenarioEditor::IsPropertyEditable() const
{
	UE_LOG(LogTemp, Warning, TEXT(" IsPropertyEditable"));
	return true;
}

/*修改了Detail属性后在此调用，进行Node更改*/
void FScenarioEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	UE_LOG(LogTemp, Warning, TEXT(" Now The DetailsView Update ! UpdateNode!"));
}



#undef LOCTEXT_NAMESPACE