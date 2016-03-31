#pragma comment(lib, "pdh.lib")

#include <pdh.h>

class CpuClass
{
public:
	CpuClass();
	CpuClass(const CpuClass&);
	~CpuClass();

	void Initialize();
	void Shutdown();
	void Frame();
	int GetCpuPercentage();

private:
	bool canReadCpu;
	HQUERY queryHandle;
	HCOUNTER counterHandle;
	unsigned long lastSampleTime;
	long cpuUsage;
};