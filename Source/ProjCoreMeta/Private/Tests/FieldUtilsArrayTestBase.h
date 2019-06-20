#pragma once

#include "FieldUtilsTestBase.h"

class FFieldUtilsArrayTestBase : public FFieldUtilsTestBase
{
public:
	FFieldUtilsArrayTestBase(const FString& InName, bool const bComplexTask);

protected:
	void AssignFields(const TSet<UField*>& InFields);

	TArray<UField*> Fields;

	void CheckField(FName InName);
};