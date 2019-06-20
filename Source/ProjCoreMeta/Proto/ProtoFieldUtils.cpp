#include "ProtoFieldUtils.h"
#include "Util/Core/LogUtilLib.h"

FString FProtoFieldUtils::GetFieldString(const UField* InField, EFieldStringFlags InFlags)
{
	FString Result;

	if((InFlags & EFieldStringFlags::ExcludeOwner) == EFieldStringFlags::None)
	{
		Result.Append(TEXT("OwnerStruct={"));		
		Result.Append(ULogUtilLib::GetNameAndClassSafe(InField->GetOwnerStruct()));	
		Result.Append(TEXT("}; "));		
	}

	Result.Append(ULogUtilLib::GetNameAndClassSafe(InField));
	
	return Result;
}

TSet<UField*> FProtoFieldUtils::GetFieldsRecursive(const UStruct* const InStruct, ELogFlags InLogFlags, EFieldIterationFlags InFieldIterationFlags)
{
	M_LOGFUNC_IF_FLAGS(InLogFlags);
	check(InStruct);

	TSet<UField*> Fields;

	TArray<const UStruct*> StructsToVisit;
	StructsToVisit.Add(InStruct);

	for(int32 StructIndex = 0; StructIndex < StructsToVisit.Num(); StructIndex++)
	{
		const UStruct* S  = StructsToVisit[StructIndex];
		M_LOG_IF_FLAGS(InLogFlags, TEXT("UStruct {%s}: "), *GetFieldString(S));
		for(UField* F : TFieldRange<UField>(S))
		{
			if( Fields.Contains(F) )
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("Skipping UStruct - Field already visited"), *GetFieldString(S));
				continue;
			}

			if(UFunction* FuncField = Cast<UFunction>(F))
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("UStruct {%s}: Skipping ufunction"), *GetFieldString(F));	
				continue;
			}

			bool bShouldAddField;
			if(UStructProperty* StructProperty = Cast<UStructProperty>(F))
			{
				UStruct* StructField = StructProperty->Struct;

				StructsToVisit.Add(StructField);
				bool bIncludeComposite = (EFieldIterationFlags::None != (InFieldIterationFlags & EFieldIterationFlags::IncludeComposite));
				if(bIncludeComposite)
				{
					M_LOG_IF_FLAGS(InLogFlags, TEXT("UStruct {%s}: Include composite flag is enabled for UStruct field"), *GetFieldString(F));
				}
				bShouldAddField = bIncludeComposite;
			}
			else
			{
				bShouldAddField = true;
			}

			if(bShouldAddField)
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("Adding field {%s}"), *GetFieldString(F));
				Fields.Add(F);
			}
		}
	}
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%d structs visited"), StructsToVisit.Num());

	return Fields;
}