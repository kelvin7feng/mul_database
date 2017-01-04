#include "ktimer.h"

#ifndef WIN32
#include <sys/time.h>
#endif

KTimer::KTimer()
{
#ifdef WIN32
	m_nFrequency.QuadPart = 200 * 1024 * 1024;
	m_nTimeStart.QuadPart = 0;
	m_nTimeStop.QuadPart = 0;
	QueryPerformanceFrequency(&m_nFrequency);
#else
	//m_nFrequency = CLOCKS_PER_SEC;
#endif
}
//---------------------------------------------------------------------------
// ����:	Start
// ����:	��ʼ��ʱ
//---------------------------------------------------------------------------
void KTimer::Start()
{
#ifdef WIN32
	QueryPerformanceCounter(&m_nTimeStart);
#else
	gettimeofday(&m_nTimeStart, NULL);
#endif
}
//---------------------------------------------------------------------------
// ����:	Stop
// ����:	ֹͣ��ʱ
//---------------------------------------------------------------------------
void KTimer::Stop()
{
#ifdef WIN32
	QueryPerformanceCounter(&m_nTimeStop);
#else
	gettimeofday(&m_nTimeStop, NULL);
#endif
}
//---------------------------------------------------------------------------
// ����:	GetElapse
// ����:	����ӿ�ʼ��ʱ�������Ѿ�����ʱ��
// ����:	unsigned int in ms
//---------------------------------------------------------------------------
unsigned int KTimer::GetElapse()
{
#ifdef WIN32
	LARGE_INTEGER nTime;
	QueryPerformanceCounter(&nTime);
	return (unsigned int)((nTime.QuadPart - m_nTimeStart.QuadPart) 
		* 1000 / m_nFrequency.QuadPart);
#else
	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec - m_nTimeStart.tv_sec) * 1000 + (tv.tv_usec - m_nTimeStart.tv_usec) / 1000;
#endif
}

unsigned long long KTimer::GetElapseEx()
{
#ifdef WIN32
	LARGE_INTEGER nTime;
	QueryPerformanceCounter(&nTime);
	return (nTime.QuadPart - m_nTimeStart.QuadPart) 
		* 1000 / m_nFrequency.QuadPart;
#else
	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec - m_nTimeStart.tv_sec) * 1000 + (tv.tv_usec - m_nTimeStart.tv_usec) / 1000;
#endif
}

//---------------------------------------------------------------------------
// ����:	GetElapseFrequency
// ����:	����ӿ�ʼ��ʱ�������Ѿ�����ʱ��
// ����:	unsigned int in frequency
//---------------------------------------------------------------------------
unsigned int KTimer::GetElapseFrequency()
{
#ifdef WIN32
	LARGE_INTEGER nTime;
	QueryPerformanceCounter(&nTime);
	return (unsigned int)(nTime.QuadPart - m_nTimeStart.QuadPart);
#endif
	return 0;
}
//---------------------------------------------------------------------------
// ����:	GetElapseFrequency
// ����:	����ӿ�ʼ��ʱ�������Ѿ�����ʱ��
// ����:	unsigned int in frequency
//---------------------------------------------------------------------------
unsigned int KTimer::GetElapseMicrosecond()
{
#ifdef WIN32
	LARGE_INTEGER nTime;
	QueryPerformanceCounter(&nTime);
	return (unsigned int)((nTime.QuadPart - m_nTimeStart.QuadPart) 
		* 1000000 / m_nFrequency.QuadPart);
#else
	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec - m_nTimeStart.tv_sec) * 1000000 + tv.tv_usec - m_nTimeStart.tv_usec;
#endif
}
//---------------------------------------------------------------------------
// ����:	GetInterval
// ����:	ȡ�ôӿ�ʼ��ֹ֮ͣ���ʱ�������Ժ���Ϊ��λ
// ����:	����ֵ
//---------------------------------------------------------------------------
unsigned int KTimer::GetInterval()
{
#ifdef WIN32
	return (unsigned int)((m_nTimeStop.QuadPart - m_nTimeStart.QuadPart) 
		* 1000 / m_nFrequency.QuadPart);
#else
	return (m_nTimeStop.tv_sec - m_nTimeStart.tv_sec) * 1000 + (m_nTimeStop.tv_usec - m_nTimeStart.tv_usec) / 1000;
#endif
}

//---------------------------------------------------------------------------
// ����:	Passed
// ����:	���Ƿ����nTime����
// ����:	nTime	����
// ����:	true	�Ѿ�����
//			false	��û�й�
//---------------------------------------------------------------------------
bool KTimer::Passed(int nTime)
{

	if (GetElapse() >= (unsigned int)nTime)
	{
		Start();
		return true;
	}
	return false;
}

