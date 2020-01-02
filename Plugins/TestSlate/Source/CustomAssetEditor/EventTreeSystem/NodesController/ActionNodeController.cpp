#include "ActionNodeController.h"
#include "ActionNodes.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/EventComponentBase.h"
#include "CustomAssetEditor/EventTreeSystem/ActiveComponent/ShowUIComponentBase.h"

#pragma optimize("",off)
/* 自动根据类型创建，其实是失败了的，并不能创建出能转换的子类 */
void UActionNodeController::Init()
{
	check(CurNode);

	UActionNodes* CurActionNode = Cast<UActionNodes>(CurNode);
	if (CurActionNode)
	{

		//根据类型创建并初始化组件，但是其实我也并不关心他是什么类型，能调用回调就可以了
		if (CurActionNode->ActiveComponent && CurActionNode->ActiveComponent->IsValidLowLevelFast())
		{
			//如果是ShowUI组件
			if (CurActionNode->ActiveComponent->StaticClass() == UShowUIComponentBase::StaticClass() || CurActionNode->ActiveComponent->GetFName() == UShowUIComponentBase::StaticClass()->GetFName())
			{
				UShowUIComponentBase* FreshObject = NewObject<UShowUIComponentBase>(CurActionNode->ActiveOjb.Get());
				FreshObject->OverDelegate.BindUObject(this, &UNodeControllerBase::ComponentsFinishCallBack);

				//注册组件
				FreshObject->RegisterComponent();
				FreshObject->AttachToComponent(CurActionNode->ActiveOjb->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				//根据Node上面的数据，设置Component
				FreshObject->SetData(CurActionNode->DataBase);
			}
			else
			{
				UE_LOG(LogTemp , Warning , TEXT("嗯这个类型现在没有写呢"));
			}
		}
	}
}
#pragma optimize("",on)