#include "ShowUIComponentBase.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/EditableText.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#pragma optimize("",off)
void UShowUIComponentBase::StartAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ShowName);

	UClass* TempSelectUI = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/StoryTest/UI/TT_PICK.TT_PICK_C'"));
	if (TempSelectUI != nullptr)
	{
		m_SelectUI = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), TempSelectUI);
		if (m_SelectUI)
		{
			m_SelectUI->AddToViewport();
			//m_SelectUI->SetVisibility(ESlateVisibility::Hidden);

			UTextBlock* TextTest = Cast<UTextBlock>(m_SelectUI->WidgetTree->FindWidget(FName("AAA")));
			if (TextTest)
			{
				TextTest->SetText(FText::FromString(ShowName));
			}
		}
	}

	AActor* actor = GetAttachmentRootActor();
	if (actor)
	{
		//actor->GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyActor::RepeatingFunction, 1.0f, true, 2.0f);
		actor->GetWorldTimerManager().SetTimer(UITimer,this,&UShowUIComponentBase::TimerOver ,1.5f , true,1.0f);
		
	}
	//FinishCallBack();
}

#pragma optimize("",on)

void UShowUIComponentBase::SetData(UComponentNodeDataBase* Data)
{
	UNodeDataShowUI* ShouUIData = Cast<UNodeDataShowUI>(Data);
	if (ShouUIData)
	{
		ShowName = ShouUIData->ShowName;
	}

}

void UShowUIComponentBase::TimerOver()
{
	AActor* actor = GetAttachmentRootActor();
	if (actor)
	{
		actor->GetWorldTimerManager().ClearTimer(UITimer);
	}

	FinishCallBack();
}

void UShowUIComponentBase::Clear()
{
	m_SelectUI->RemoveFromViewport();
	m_SelectUI = nullptr;
	Super::Clear();
}