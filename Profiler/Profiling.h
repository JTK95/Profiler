#pragma once

class CProfile
{
public:
    struct ProfileInfo
    {
        bool bFlag = false; // 프로파일의 사용 여부. (배열시에만)
        char TagName[64]; // 프로파일 샘플 이름.

        LARGE_INTEGER lStartTime;
        LARGE_INTEGER lEndTime;

        __int64 iTotalTime;
        __int64 iMin[2]; // 최소 사용시간 카운터 Time. (초단위로 계산하여 저장 / [0] 가장최소 [1] 다음 최소 [2])
        __int64 iMax[2]; // 최대 사용시간 카운터 Time. (초단위로 계산하여 저장 / [0] 가장최대 [1] 다음 최대 [2])
        __int64 iCall;
        __int64 iAverage;
    };

    CProfile(const char* TagName);
    ~CProfile();

private:
    friend void ProfileBegin(const char* TagName);
    friend void ProfileEnd();
    friend void ProfileDataOutText(const char* TagName);
};

//----------------------------------
// Profile 시작, 끝 함수
//----------------------------------
void ProfileBegin(const char* TagName);
void ProfileEnd();

//----------------------------------
// Profiling 된 데이터 text로 출력
//----------------------------------
void ProfileDataOutText(const char* TagName);

//----------------------------------
// 컴파일 제외 함수
//----------------------------------
#define PRO_BEGIN(TagName) ProfileBegin(TagName)
#define PRO_END() ProfileEnd()