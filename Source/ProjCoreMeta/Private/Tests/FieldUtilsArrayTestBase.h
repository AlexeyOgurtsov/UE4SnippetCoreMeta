#pragma once

#include "FieldUtilsTestBase.h"

class FFieldUtilsArrayTestBase : public FFieldUtilsTestBase
{
public:
	FFieldUtilsArrayTestBase(const FString& InName, bool const bComplexTask);

protected:
	TArray<UField*> Array;
};