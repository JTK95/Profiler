#pragma once

class CProfile
{
public:
    struct ProfileInfo
    {
        bool bFlag = false; // ���������� ��� ����. (�迭�ÿ���)
        char TagName[64]; // �������� ���� �̸�.

        LARGE_INTEGER lStartTime;
        LARGE_INTEGER lEndTime;

        __int64 iTotalTime;
        __int64 iMin[2]; // �ּ� ���ð� ī���� Time. (�ʴ����� ����Ͽ� ���� / [0] �����ּ� [1] ���� �ּ� [2])
        __int64 iMax[2]; // �ִ� ���ð� ī���� Time. (�ʴ����� ����Ͽ� ���� / [0] �����ִ� [1] ���� �ִ� [2])
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
// Profile ����, �� �Լ�
//----------------------------------
void ProfileBegin(const char* TagName);
void ProfileEnd();

//----------------------------------
// Profiling �� ������ text�� ���
//----------------------------------
void ProfileDataOutText(const char* TagName);

//----------------------------------
// ������ ���� �Լ�
//----------------------------------
#define PRO_BEGIN(TagName) ProfileBegin(TagName)
#define PRO_END() ProfileEnd()