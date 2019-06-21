#include "FieldUtilsArrayTestBase.h"
#include "Proto/ProtoFieldUtils.h"
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
		if(nullptr == ppField) 
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

	const UField* F;
	{
		M_LOGBLOCK(TEXT("FindFieldWithName"));
		F = FindFieldWithName(Fields, InName);
	}
	TestNotNull(FString::Printf(TEXT("Field with name \"%s\" is expected to be included"), *InName.ToString()), F);
}

void FFieldUtilsArrayTestBase::CheckFieldsIncluded(const UStruct* InStruct)
{
	M_LOGFUNC_MSG(TEXT("Checking that fields of struct \"%s\" included"), *ULogUtilLib::GetNameAndClassSafe(InStruct));
	check(InStruct);
	int32 FieldIndex = 0;
	for(UField* ExpectedField : TFieldRange<UField>(InStruct))
	{
		if(nullptr == Cast<const UFunction>(ExpectedField))			
		{
			M_LOGFUNC_MSG(TEXT("Checking expected field N %d: {%s}"), FieldIndex, *FProtoFieldUtils::GetFieldString(ExpectedField));									
			CheckField(ExpectedField->GetFName());
		}
		else
		{
			M_LOG(TEXT("Skipping expected field {%s}: it's UFunction"), *FProtoFieldUtils::GetFieldString(ExpectedField));
		}
		FieldIndex++;
	}
	M_LOG(TEXT("%d expected fields checked"), FieldIndex);
}

void FFieldUtilsArrayTestBase::AssignFields(const TSet<UField*>& InFields)
{
	Fields = InFields.Array();
}