#include "Job.h"
#include "../../Resource/Resource.h"

Job::Job(const string & name)
	: GameObject(name)
{
	m_unionRank = 0;
	m_unionRaiderEffect = 0;
	m_jobKind = 0;
	m_mainStat = MAIN_STAT::STR;
}

Job::~Job()
{
}

bool Job::Initialize(void* p)
{
	unordered_map<string, unsigned char> jobInfo = GET_INSTANCE(Resource)->GetJobInfo();
	auto iter = jobInfo.find(m_name);
	if (iter == jobInfo.end())
		return false;

	m_mainStat = static_cast<MAIN_STAT>((*iter).second);

	return true;
}

void Job::Update()
{
}

