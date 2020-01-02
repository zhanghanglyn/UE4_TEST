#include "ShowUIComponentBase.h"

void UShowUIComponentBase::StartAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ShowName);
	FinishCallBack();
}

void UShowUIComponentBase::SetData(UComponentNodeDataBase* Data)
{
	UNodeDataShowUI* ShouUIData = Cast<UNodeDataShowUI>(Data);
	if (ShouUIData)
	{
		ShowName = ShouUIData->ShowName;
	}

}