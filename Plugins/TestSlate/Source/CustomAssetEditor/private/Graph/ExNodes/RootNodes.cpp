#include "RootNodes.h"

URootNodes::URootNodes()
{
	NodeName = "Root";
	bOpenGraph = false;
}

void URootNodes::AllocateDefaultPins()
{
	//CreatePin(EEdGraphPinDirection::EGPD_Input,FName("TestPinIN") ,TEXT("IN"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, FName("TestPinOUT"), TEXT("OUT"));
}

UEdGraphPin* URootNodes::GetOutPutPin()
{
	return Pins[0];
}