#pragma once

class UField;
class UStruct;

class FProtoFieldUtils
{
public:
	/**
	* Returns all fields recursively from the given struct.
	*/
	static TArray<UField*> GetFieldsRecursive(const UStruct* InStruct);

private:
};