
#include "SLayoutDetail.h"

#define  LOCTEXT_NAMESPACE "SLayoutDetail"

void SLayoutDetail::Construct(const FArguments& InArgs)
{
	this->ChildSlot
	[
        SNew(SDetail)
	];
}

#undef   LOCTEXT_NAMESPACE