#include "MetaTestLib.h"
#include "Test/TestClass.h"
#include "Util/Core/LogUtilLib.h"

namespace
{
	class FFieldUtils
	{
	public:
		static void LogField(UField* InField)
		{
			if(InField == nullptr) 
			{
				UE_LOG(MyLog, Log, TEXT("nullptr"));
			}
			else
			{
				FString const OwnerClass = InField->GetOwnerClass() ? InField->GetOwnerClass()->GetName() : FString(TEXT("nullptr"));
				FString const OwnerStruct = InField->GetOwnerStruct() ? InField->GetOwnerStruct()->GetName() : FString(TEXT("nullptr"));
				UE_LOG(MyLog, Log, TEXT("Name=\"%s\" Class=\"%s\"; OwnerClass=\"%s\"; OwnerStruct=\"%s\""), *InField->GetName(), *InField->GetClass()->GetName(), *OwnerClass, *OwnerStruct);
			}
		}

		static void LogFields
		(
			UStruct* S, 
			EFieldIteratorFlags::SuperClassFlags InSuperClassFlags = EFieldIteratorFlags::SuperClassFlags::IncludeSuper
		)
		{
			check(S);
			for(UField* Field : TFieldRange<UField>(S, InSuperClassFlags))
			{
				LogField(Field);
			}
		}
	};
} // anonymous

void UMetaTestLib::QuickTest(UObject* WorldContextObject)
{
	M_LOGFUNC();
	checkNoRecursion();

	{	
		M_LOGBLOCK(TEXT("%s::StaticStruct()"), *FTestStruct::StaticStruct()->GetName());		
		//FTestStruct TestStruct;

		// Fails to compile
		//FFieldUtils::LogFields(&FTestStruct);
		//FFieldUtils::LogFields(&TestStruct);

		// Compiles well
		FFieldUtils::LogFields(FTestStruct::StaticStruct());
	}

	{
		M_LOGBLOCK(TEXT("%s::StaticClass()"), *UTestClass::StaticClass()->GetName());		
		//auto Obj = NewObject<UTestClass>(WorldContextObject, UTestClass::StaticClass());
		// Compiles well
		FFieldUtils::LogFields(UTestClass::StaticClass());
	}

	{
		M_LOGBLOCK(TEXT("%s::StaticClass()"), *UTestBaseClass::StaticClass()->GetName());		
		// Compiles well
		FFieldUtils::LogFields(UTestBaseClass::StaticClass());
	}
}

void UMetaTestLib::IterateFieldsTest(UObject* WorldContextObject)
{
	M_LOGFUNC();
	checkNoRecursion();
}