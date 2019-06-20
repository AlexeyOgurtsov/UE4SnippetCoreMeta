#include "FieldUtilsArrayTestBase.h"
#include "Util/Core/LogUtilLib.h"

FFieldUtilsArrayTestBase::FFieldUtilsArrayTestBase(const FString& InName, bool const bComplexTask) 
: FFieldUtilsTestBase {InName, bComplexTask}
{
}

namespace
{
	UField* FindFieldWithName(const TArray<UField*>& InFields, FName InName)
	{
		UField* const * ppField = InFields.FindByPredicate
		(
			[InName](const UField* F)
			{
				check(F); 
				return F->GetFName() == InName; 
			}
		);
		if(nullptr) 
		{
			return nullptr;
		}
		return *ppField;
	}
} // anonymous

void FFieldUtilsArrayTestBase::CheckField(FName InName)
{
	M_LOGFUNC_MSG(TEXT("Checking expected field with name \"%s\""), *InName.ToString());
	checkNoRecursion();

	const UField* const F = FindFieldWithName(Fields, InName);
	TestNotNull(FString::Printf(TEXT("Field with name \"%s\" is expected to be included"), *InName.ToString()), F);
}

void FFieldUtilsArrayTestBase::AssignFields(const TSet<UField*>& InFields)
{
	Fields = InFields.Array();
}