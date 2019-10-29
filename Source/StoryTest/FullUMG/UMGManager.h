// Fill out your copyright notice in the Description page of Project Settings.
//@ �ź� ��ע
/*
	��ʵҲ���Բ�����FullScreenWidgetBaseֱ��ʹ��UUserwidget��������Ե�һЩ����������������������ʹ��,
	��Ϊ���˾��ã���һ��Ҫ�̳е�
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Script/FullScreenWidgetBase.h"
#include "Script/FullScreenRoot.h"
#include "UMG/Public/Components/CanvasPanelSlot.h"
#include "UMGManager.generated.h"

/**
 * UMG������ ���� �����GameInstance��
 */
UCLASS(BlueprintType , Blueprintable)
class STORYTEST_API UUMGManager : public UObject
{
	GENERATED_BODY()

private:
	//static UUMGManager* Instace;

//ʵ�ָ��෽����ص�
public:
	UUMGManager(const FObjectInitializer& ObjectInitializer);
	
	/*static UUMGManager* GetInstance()
	{
		static UUMGManager* Instace;
		if (Instace == nullptr)
			Instace = NewObject<UUMGManager>();
		return Instace;
	}*/

/************************************************************************/
/*						ֱ�Ӵ�������Ļ���                             */
/************************************************************************/
public:
	//����Ļ���һ��UMG
	UFullScreenWidgetBase* CreateScreenWidget(FString _widgetBlueprintPath, UWorld* _world, TSubclassOf<UFullScreenWidgetBase> _widgetType, FString _widgetName, int32 _zorder = 0);
	//����Ļ���һ��UMG
	template<typename T>
	T* CreateScreenWidget(FString _widgetBlueprintPath,UWorld* _world, TSubclassOf<UFullScreenWidgetBase> _widgetType, FString _widgetName, int32 _zorder = 0)
	{
		if (m_ScreenWidget.Num() > 0 && m_ScreenWidget.Find(_widgetName) != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("this name is aleady in the map!!!!"));
			return nullptr;
		}

		UClass* Temp_Widget = LoadClass<T>(NULL, _widgetBlueprintPath.GetCharArray().GetData());
		if (Temp_Widget != nullptr)
		{
			T* NewWidget = CreateWidget<T>(_world, Temp_Widget);
			if(NewWidget != nullptr)
				(Cast<UFullScreenWidgetBase>(NewWidget))->AddToViewport(_zorder);
			m_ScreenWidget.Add(_widgetName, NewWidget);
			//m_WidgetTypeRelate.Add(_widgetName, _widgetType);
			return NewWidget;
		}
		return nullptr;
	}

	//��ȡUMG
	UFullScreenWidgetBase* GetScreenWidget(FString _widgetName);
	//��ȡUMG
	template<typename T1>
	T1* GetScreenWidget(FString _widgetName)
	{
		if (m_ScreenWidget.Num() > 0 && m_ScreenWidget.Find(_widgetName) != nullptr)
		{
			//m_WidgetTypeRelate[1]::Class aa = Cast< m_WidgetTypeRelate[1]>(*m_ScreenWidget.Find(_widgetName));
			return Cast<T1>(*m_ScreenWidget.Find(_widgetName));
		}
		return nullptr;
	}

	//��ȡ��Ӧ���ֵ�UMGType
	TSubclassOf<UFullScreenWidgetBase> GetWidgetTypeByName(FString _widgetName);

	//���Widget
	void ClearWidget(FString _widgetName);
	void ClearAll();

	//���õ��GameMode����PlayerMode�¼�
	void SetInputMode(UWorld* _world, FInputModeDataBase& InData);

protected:
	//�������ּ�¼Widget
	UPROPERTY()
	TMap<FString, UFullScreenWidgetBase*> m_ScreenWidget;
	//��¼ÿ�����ֶ�Ӧ�����ͣ�����ת��  //��ʱ�о�ûʲô���� 10.22
	TMap<FString, TSubclassOf<UFullScreenWidgetBase>> m_WidgetTypeRelate;

/************************************************************************/
/*						������GameInstance���                          */
/************************************************************************/
public:
	//�ڴ���GameInstance GameViewportClient�м�����ڵ�UI ��UI���ᱻ���
	void CreateInstanceRootWidget(UGameInstance* GameInstance);

	//��InstanceWidget�����UMG
	UFullScreenWidgetBase* CreateInstanceWidget(FString _widgetBlueprintPath, UWorld* _world, FString _widgetName, int32 _zorder = 0);

	//ɾ��ȫ��UMG
	void DeleteInsUMGByName(FString _widgetName);
	//���ȫ��UMG
	void ClearInsUMG();

protected:
	//���ڵ��widget
	UPROPERTY()
	UFullScreenRoot* m_RootWidget;
	//�洢�ڸ��ڵ��ϵ�UI��Array
	UPROPERTY()
	TArray<UFullScreenWidgetBase*> m_InsWidgetList;
	//������¼Widget���ֶ�Ӧ��List�е�Index
	TMap<FString, int32> m_InsWidgetIndexList;

};
