#include "EventComponentBase.h"

void UEventComponentBase::FinishCallBack() {
	OverDelegate.ExecuteIfBound(FName(""));
	Clear();
};
