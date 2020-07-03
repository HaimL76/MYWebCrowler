#pragma once
#include <string>
#include <windows.h>

using namespace std;

class ResolveHostName
{
public:
	virtual string& Resolve(string& hostName) = 0;
};

class RegularResolveHostName : public ResolveHostName
{
public:
    virtual string& Resolve(string& hostName);
};

