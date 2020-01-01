#include "ShowUIComponentBase.h"

void UShowUIComponentBase::StartAction()
{
	UE_LOG(LogTemp, Warning, TEXT("我进行了Action咯~~~"));
	FinishCallBack();
}