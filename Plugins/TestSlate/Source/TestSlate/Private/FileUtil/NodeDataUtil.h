/*
	声明一个Node的数据结构体，暂时以技能树为目标设计结构
*/
#pragma once
#include "CoreMinimal.h"

//单个节点的数据结构
struct NodeData
{
public:
	struct Detail
	{
		FString SkillName;	//
	};

public:
	NodeData(int32 _DataID) :DataID(_DataID) {};

public:
	int32 DataID = -1;		//当前节点的ID
	int32 ParentID = -1;	//父节点ID
	int32 ChildID = -1;		//子节点ID
	FVector2D Pos;			//创建位置
	FVector2D LinePos;	//连线位置

	Detail DataDetail;

};

//总数据,初始化时根据该数据初始化节点，存储时将所有节点数据便利并存入
struct TreeData
{
public:
	TMap<int32 , NodeData*> DataList;	//key为索引ID
};

//数据的管理类
class TreeDataMgr
{
public:
	//读取所有DATA数据
	static TreeData ReadAllData();
	//保存所有数据
	static void SaveAllData();
	
};