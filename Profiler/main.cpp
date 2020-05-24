#include "stdafx.h"
#include "Profiling.h"

int main()
{
	for (int i = 0; i < 100000 ; i++)
	{
		CProfile profile("Func1");
	}

	ProfileDataOutText("Func1");

	return 0;
}