// Fill out your copyright notice in the Description page of Project Settings.


#include "UMGManager.h"

//UUMGManager* UUMGManager::Instace = nullptr;
UUMGManager::UUMGManager(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	m_ScreenWidget.Empty();
}

UFullScreenWidgetBase* UUMGManager::CreateScreenWidget(FString _widgetBlueprintPath, UWorld * _world, TSubclassOf<UFullScreenWidgetBase> _widgetType, FString _widgetName , int32 _zorder)
{
	if (m_ScreenWidget.Num() > 0 && m_ScreenWidget.Find(_widgetName) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("this name is aleady in the map!!!!"));
		return nullptr;
	}
	UClass* Temp_Widget = LoadClass<UFullScreenWidgetBase>(NULL, _widgetBlueprintPath.GetCharArray().GetData());
	if (Temp_Widget != nullptr)
	{
		UFullScreenWidgetBase *NewWidget = CreateWidget<UFullScreenWidgetBase>(_world, Temp_Widget);
		if (NewWidget != nullptr)
			NewWidget->AddToViewport(_zorder);

		m_ScreenWidget.Add(_widgetName, NewWidget);
		//m_WidgetTypeRelate.Add(_widgetName, _widgetType);

		return NewWidget;
	}

	return nullptr;
}

UFullScreenWidgetBase* UUMGManager::GetScreenWidget(FString _widgetName)
{
	if (m_ScreenWidget.Find(_widgetName) != nullptr)
	{
		return *m_ScreenWidget.Find(_widgetName);
	}
	return nullptr;
}

TSubclassOf<UFullScreenWidgetBase> UUMGManager::GetWidgetTypeByName(FString _widgetName)
{
	if (m_WidgetTypeRelate.Num() > 0 && m_WidgetTypeRelate.Find(_widgetName) != NULL)
	{
		return *m_WidgetTypeRelate.Find(_widgetName);
	}

	return TSubclassOf<UFullScreenWidgetBase>();
}

void UUMGManager::ClearWidget(FString _widgetName)
{
	if (m_ScreenWidget.Num() > 0)
	{
		UFullScreenWidgetBase *tempWidget = *m_ScreenWidget.Find(_widgetName);
		if (tempWidget->IsInViewport())
			tempWidget->RemoveFromViewport();

		tempWidget = nullptr;
		m_ScreenWidget.Remove(_widgetName);
		//����¶�Ӧ��ϵ
		//if (m_WidgetTypeRelate.Num() > 0 && m_WidgetTypeRelate.Find(_widgetName) != NULL )
			//m_WidgetTypeRelate.Remove(_widgetName);
	}
}

void UUMGManager::ClearAll()
{
	if (m_ScreenWidget.Num() > 0)
	{
		//for (TMap<FString, UFullScreenWidgetBase*>::TIterator it = m_ScreenWidget.CreateIterator(); it; ++it)
		//{
		//	if (it->Value->IsInViewport())
		//		it->Value->RemoveFromViewport();
		//}
		for (auto& Elem : m_ScreenWidget)
		{
			if (Elem.Value != nullptr && Elem.Value->IsInViewport())
				Elem.Value->RemoveFromViewport();
		}

	}
	m_ScreenWidget.Empty();
	//m_WidgetTypeRelate.Empty();
}

void UUMGManager::SetInputMode(UWorld* _world, FInputModeDataBase& InData)
{
	if (_world != nullptr)
		_world->GetFirstPlayerController()->SetInputMode(InData);
}


/************************************************************************/
/*						������GameInstance���                          */
/************************************************************************/
void UUMGManager::CreateInstanceRootWidget(UGameInstance * GameInstance)
{
	if (m_RootWidget != nullptr)
		return;

	//�޸�Ϊ����Ҫ�ⲿ������ͼ��ֱ�Ӵ�����һ��UFullScreenRoot���͵�UI�����ҳ�ʼ�����ڵ�
	FString rootPath = "WidgetBlueprint'/Game/StoryTest/UI/BP_RootWidget.BP_RootWidget_C'";
	UClass* Temp_Widget = LoadClass<UFullScreenRoot>(NULL, rootPath.GetCharArray().GetData());
	if (Temp_Widget)
	{
		m_RootWidget = CreateWidget<UFullScreenRoot>(GameInstance->GetWorld(), UFullScreenRoot::StaticClass());
		if (m_RootWidget != nullptr)
		{
			//�ֶ�����USERWIDGET��Root
			m_RootWidget->WidgetTree->RootWidget = m_RootWidget->WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("Root"));
			m_RootWidget->Root = Cast<UCanvasPanel>(m_RootWidget->WidgetTree->RootWidget);
			if (m_RootWidget->Root != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("UFullScreenRoot Add Root Error!!!!"));
			}

			GameInstance->GetGameViewportClient()->AddViewportWidgetContent(m_RootWidget->TakeWidget(), 0);
			FVector2D Result;
			GameInstance->GetGameViewportClient()->GetViewportSize(Result);
		}
	}
	
}

//��InstanceWidget�����UMG
UFullScreenWidgetBase* UUMGManager::CreateInstanceWidget(FString _widgetBlueprintPath, UWorld * _world, FString _widgetName, int32 _zorder)
{
	if (m_RootWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("the m_RootWidget IS null!!!!!!!!!!!"));
		return nullptr;
	}
	if (m_RootWidget->Root == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("the m_RootWidget->Root IS null!!!!!!!!!!!"));
		return nullptr;
	}

	UClass* Temp_Widget = LoadClass<UFullScreenWidgetBase>(NULL, _widgetBlueprintPath.GetCharArray().GetData());
	if (Temp_Widget != nullptr)
	{
		UFullScreenWidgetBase *NewWidget = CreateWidget<UFullScreenWidgetBase>(_world, Temp_Widget);
		if (NewWidget != nullptr)
		{
			m_RootWidget->Root->AddChildToCanvas(NewWidget);
			UCanvasPanelSlot * Canvas = Cast <UCanvasPanelSlot>(NewWidget->Slot);
			if (Canvas != nullptr)
			{
				FVector2D viewPortSize;
				_world->GetGameViewport()->GetViewportSize(viewPortSize);
				Canvas->SetSize(viewPortSize);
			}
		}

		m_InsWidgetList.Push(NewWidget);
		//��¼һ��INDEX�����ֵĹ�ϵ
		m_InsWidgetIndexList.Add(_widgetName, (m_InsWidgetList.Num() - 1));

		return NewWidget;
	}

	return nullptr;
}

//ɾ��ȫ��UMG
void UUMGManager::DeleteInsUMGByName(FString _widgetName)
{
	if (m_InsWidgetList.Num() > 0 && m_InsWidgetIndexList.Num() > 0 && m_InsWidgetIndexList.Find(_widgetName) != nullptr)
	{
		int32 index = *m_InsWidgetIndexList.Find(_widgetName);
		if (m_InsWidgetList[index] != nullptr)
		{
			UFullScreenWidgetBase *deleteWidget = m_InsWidgetList[index];
			deleteWidget->RemoveFromParent();
			deleteWidget = nullptr;
			m_InsWidgetList.RemoveAt(index);
			m_InsWidgetIndexList.Remove(_widgetName);
		}
	}
}

void UUMGManager::ClearInsUMG()
{
	if (m_InsWidgetList.Num() > 0)
	{
		for (int32 i = 0; i < m_InsWidgetList.Num(); i++)
		{
			if (m_InsWidgetList[i] != nullptr)
			{
				m_InsWidgetList[i]->RemoveFromParent();
				m_InsWidgetList[i] = nullptr;
			}
		}
	}
	m_InsWidgetList.Empty();
	m_InsWidgetIndexList.Empty();
}