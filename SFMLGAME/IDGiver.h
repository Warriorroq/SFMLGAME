#pragma once

using namespace std;

class IDgGiver 
{
public:
	static long IncreaseLastId()
	{
		return _lastId++;
	}
private:
	static long _lastId;
};