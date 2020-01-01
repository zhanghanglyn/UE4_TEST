#include "ActionNodeController.h"
#include "ActionNodes.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/EventComponentBase.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/ShowUIComponentBase.h"

#pragma optimize("",off)
/* 自动根据类型创建，其实是失败了的，并不能创建出能转换的子类 */
void UActionNodeController::Init()
{
	check(CurNode);

	//测试类型
	UActionNodes* TESTNode = Cast<UActionNodes>(CurNode);
	if (TESTNode)
	{
		//根据类型创建并初始化组件，但是其实我也并不关心他是什么类型，能调用回调就可以了
		if (TESTNode->ActiveComponent && TESTNode->ActiveComponent->IsValidLowLevelFast())
		{
			/*auto FreshObject = NewObject<UEventComponentBase>(TESTNode->ActiveOjb.Get(), TESTNode->ActiveComponent->GetFName(), RF_NoFlags, TESTNode->ActiveComponent->GetDefaultObject());
			//TESTNode->ActiveComponent* FreshObject = NewObject<TESTNode->ActiveComponent>();
			FreshObject->OverDelegate.BindUObject(this, &UNodeControllerBase::ComponentsFinishCallBack);

			//注册组件
			FreshObject->RegisterComponent();
			FreshObject->AttachToComponent(TESTNode->ActiveOjb->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);*/

			//如果是ShowUI组件
			if (TESTNode->ActiveComponent->StaticClass() == UShowUIComponentBase::StaticClass() || TESTNode->ActiveComponent->GetFName() == UShowUIComponentBase::StaticClass()->GetFName())
			{
				UShowUIComponentBase* FreshObject = NewObject<UShowUIComponentBase>(TESTNode->ActiveOjb.Get());
				FreshObject->OverDelegate.BindUObject(this, &UNodeControllerBase::ComponentsFinishCallBack);

				//注册组件
				FreshObject->RegisterComponent();
				FreshObject->AttachToComponent(TESTNode->ActiveOjb->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			}
			else
			{
				UE_LOG(LogTemp , Warning , TEXT("嗯这个类型现在没有写呢"));
			}
		}
	}
}
#pragma optimize("",on)