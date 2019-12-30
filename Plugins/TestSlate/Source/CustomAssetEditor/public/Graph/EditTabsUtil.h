#pragma once

#include "CoreMinimal.h"

struct FScenarioEditorTabsUtil
{
	// Details��ͨ��ID
	static const FName GraphDetailsID;
	static const FName SearchID;

	// Editor��ͨ��ID
	static const FName GraphEditorID;
};

//���нڵ��Լ�Pinʹ�õ����ƶ���
struct FScenarioNodeUtil
{
	static const FName NodeCategoryNormal;
	static const FName NodeCategoryRoot;
	static const FName NodeCategoryEnd;
};

struct FScenarioPinUtil
{
	static const FName SubPinCategoryNormal;	//��ͨ�ڵ��SubPin����ʱֻ����һ������������PinFactory�Ĵ���
	static const FName SubPinCategoryRoot;		//Root��End�����ⲻ�ܵ������ӵ�
	static const FName SubPinCategoryEnd;		//Root��End�����ⲻ�ܵ������ӵ�

	static const FName PinCategoryNotAllow;	//�������κ�����
	static const FName PinCategoryNormal;	//��ͨPin��ֻ����һ������
	static const FName PinCategoryMulti;	//�������Ӷ��Pin
};