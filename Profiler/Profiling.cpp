#include "stdafx.h"
#include "Profiling.h"

#define INFO_COUNT 100
#define MicroSecond 1000000

CProfile::ProfileInfo proFileInfo[INFO_COUNT];

//----------------------------------
// Profile 시작, 끝 함수
//----------------------------------
void ProfileBegin(const char* TagName)
{
	for (int i = 0; i < INFO_COUNT; i++)
	{
		if (strcmp(proFileInfo[i].TagName, TagName) == 0)
		{
			continue;
		}

		// 사용중이라면..
		if (proFileInfo[i].bFlag)
		{
			continue;
		}
		
		proFileInfo[i].bFlag = true;
		strcpy_s(proFileInfo[i].TagName, sizeof(char) * 64, TagName);

		QueryPerformanceCounter(&proFileInfo[i].lStartTime);

		break;
	}
}

void ProfileEnd()
{
	for (int i = 0; i < INFO_COUNT; i++)
	{
		QueryPerformanceCounter(&proFileInfo[i].lEndTime);

		LARGE_INTEGER Freq;
		QueryPerformanceFrequency(&Freq);

		// Run-Time (㎲)
		__int64 iRunTime = ((proFileInfo[i].lEndTime.QuadPart - proFileInfo[i].lStartTime.QuadPart)
			/ (Freq.QuadPart / MicroSecond));
		
		// Total Time
		proFileInfo[i].iTotalTime += iRunTime;
		
		// Call Count
		proFileInfo[i].iCall += 1;

		// Average
		proFileInfo[i].iAverage = (proFileInfo[i].iTotalTime / proFileInfo[i].iCall);

		// Min
		for (int j = 0; j < 2; j++)
		{
			if (proFileInfo[i].iMin[j] < iRunTime)
			{
				continue;
			}
			
			proFileInfo[i].iMin[j] = iRunTime;
			break;
		}
		
		// Max
		for (int j = 0; j < 2; j++)
		{
			if (proFileInfo[i].iMax[j] > iRunTime)
			{
				continue;
			}

			proFileInfo[i].iMax[j] = iRunTime;
			break;
		}

		break;
	}
}

//----------------------------------
// Profiling 된 데이터 text로 출력
//----------------------------------
void ProfileDataOutText(const char* TagName)
{
	string str1 = "-------------------------------------------------------------------------------";
	string str2 = "           Name  |     Average  |        Min   |        Max   |      Call |";
	string str3 = "-------------------------------------------------------------------------------";
	string str4 = "-------------------------------------------------------------------------------";

	fstream proFileText("Profiler.txt", ios::out); //쓰기 모드
	if (!proFileText)
	{
		puts("Profiler.txt Open Error");
		return;
	}

	proFileText << str1 << endl;
	proFileText << str2 << endl;
	proFileText << str3 << endl;

	for (int i = 0; i < INFO_COUNT; i++)
	{	
		if (i > 0)
		{
			if (strcmp(proFileInfo[i - 1].TagName, TagName) == 0)
			{
				break;
			}
		}

		proFileText << "           " << proFileInfo[i].TagName << "  |";
		proFileText << "     " << proFileInfo[i].iAverage << "㎲  |";
		proFileText << "        " << proFileInfo[i].iMin[0] << "㎲  |";
		proFileText << "        " << proFileInfo[i].iMax[0] << "㎲  |";
		proFileText << "      " << proFileInfo[i].iCall << "  |" << endl;
	}

	proFileText << str4 << endl;

	proFileText.close();
}

CProfile::CProfile(const char* TagName)
{
	PRO_BEGIN(TagName);
}

CProfile::~CProfile()
{
	PRO_END();
}