#include "ScenarioNodeBase.h"

UScenarioNodeBase::UScenarioNodeBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

void UScenarioNodeBase::AllocateDefaultPins()
{
	//CreatePin(EEdGraphPinDirection::EGPD_Input,FName("TestPinIN") ,TEXT("IN"));
	CreatePin(EEdGraphPinDirection::EGPD_Input, FName("TestPinOUT"), TEXT("OUT"));
}
