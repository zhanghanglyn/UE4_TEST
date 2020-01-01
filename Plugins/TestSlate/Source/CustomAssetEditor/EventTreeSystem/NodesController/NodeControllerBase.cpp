#include "NodeControllerBase.h"
#include "ActionNodes.h"

void UNodeControllerBase::ControllerFinish()
{
	BControlOver = true;
	OverDelegate.ExecuteIfBound(ControllerCategory);
}

/* 根据Node上的数据进行Controller以及对应的Actor的初始化以及组件的赋予 */
void UNodeControllerBase::Init()
{
	check(CurNode);

	//测试类型
	UActionNodes* TESTNode = Cast<UActionNodes>(CurNode);
	if (TESTNode)
	{
		//TESTNode->ActiveOjb

		//根据类型创建并初始化组件，但是其实我也并不关心他是什么类型，能调用回调就可以了
		if (TESTNode->ActiveComponent && TESTNode->ActiveComponent->IsValidLowLevelFast())
		{
			//ComponentBase = NewObject<UEventComponentBase>();
			auto FreshObject = NewObject<UEventComponentBase>(this, TESTNode->ActiveComponent->GetFName(), RF_NoFlags, TESTNode->ActiveComponent.GetDefaultObject());
			FreshObject->OverDelegate.BindUObject(this, &UNodeControllerBase::ComponentsFinishCallBack);

			FreshObject->RegisterComponent();
			FreshObject->AttachToComponent(TESTNode->ActiveOjb->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
		//	ComponentBase->RegisterComponent();
		//WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void UNodeControllerBase::ComponentsFinishCallBack(FName Paramm)
{
	ControllerFinish();
}