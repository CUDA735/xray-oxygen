#include "stdafx.h"
#include "thread_utils.h"

xrCriticalSection::xrCriticalSection()
{
	InitializeCriticalSectionEx(&Section, 250, 0);
}

xrCriticalSection::~xrCriticalSection()
{
	DeleteCriticalSection(&Section);
}

void xrCriticalSection::Enter()
{
	EnterCriticalSection(&Section);
	LockCounter++;
}

void xrCriticalSection::Leave()
{
	//if (!LockCounter.load(std::memory_order::memory_order_relaxed))
	//{
	//	FATAL("Section is not locked");
	//	return;
	//}
	u32 number = LockCounter--;
	if (number > 0xFFFFFFFAu)
	{
		LockCounter = 0;
	}
	LeaveCriticalSection(&Section);
}

bool xrCriticalSection::IsLocked()
{
	return LockCounter;
}

xrCriticalSectionGuard::xrCriticalSectionGuard(xrCriticalSection& InSection)
	: Section(InSection)
{
	Section.Enter();
}

xrCriticalSectionGuard::~xrCriticalSectionGuard()
{
	Section.Leave();
}


#include <process.h>

struct	THREAD_STARTUP
{
	thread_t* entry;
	string128 name;
	void* args;
};

void __cdecl thread_entry(void*	_params)
{
	// initialize
	THREAD_STARTUP* startup = (THREAD_STARTUP*)_params;
	PlatformUtils.SetCurrentThreadName(startup->name);
	Profiling.SetCurrentThreadName(startup->name);

	thread_t* entry = startup->entry;
	void* arglist = startup->args;
	xr_delete(startup);
	_initialize_cpu_thread();

	// call
	entry(arglist);
}
HANDLE thread_spawn(thread_t* entry, const char* name, unsigned stack, void* arglist)
{
	THREAD_STARTUP* startup = new THREAD_STARTUP();
	startup->entry = entry;
	startup->args = arglist;

	u32 ThreadNameLen = xr_strlen(name);
	VERIFY(ThreadNameLen < sizeof(startup->name));
	memcpy(startup->name, name, ThreadNameLen);

	uintptr_t hThread = _beginthread(thread_entry, stack, startup);
	return reinterpret_cast<HANDLE> (hThread);
}

xrSharedCriticalSectionGuard::xrSharedCriticalSectionGuard(xrCriticalSection& InSection)
	: pSection(&InSection)
{
	pSection->Enter();
	pReference = new xr_atomic_u32();
	(*pReference) = 1;
}

xrSharedCriticalSectionGuard::xrSharedCriticalSectionGuard(const xrSharedCriticalSectionGuard& InSharedSection)
	: pSection(InSharedSection.pSection), pReference(InSharedSection.pReference)
{
	(*pReference)++;
}

xrSharedCriticalSectionGuard::~xrSharedCriticalSectionGuard()
{
	ConditionalFreeLock();
}

void xrSharedCriticalSectionGuard::ConditionalFreeLock()
{
	u32 refCount = --(*pReference);

	if (refCount == 0)
	{
		pSection->Leave();
		pSection = nullptr;
		delete pReference;
	}
}

xrSharedCriticalSectionGuard& xrSharedCriticalSectionGuard::operator=(const xrSharedCriticalSectionGuard& Other)
{
	ConditionalFreeLock();

	VERIFY(Other.pSection   != nullptr);
	VERIFY(Other.pReference != nullptr);

	pSection = Other.pSection;
	pReference = Other.pReference;

	(*pReference)++;

	return *this;
}

xrConditionalVariable::xrConditionalVariable()
{
	InitializeConditionVariable(&Variable);
}

xrConditionalVariable::~xrConditionalVariable()
{}

void xrConditionalVariable::WakeOne()
{
	WakeConditionVariable(&Variable);
}

void xrConditionalVariable::WakeAll()
{
	WakeAllConditionVariable(&Variable);
}

void xrConditionalVariable::Sleep(xrCriticalSection& AcquiringCS)
{
	SleepConditionVariableCS(&Variable, &AcquiringCS.Section, INFINITE);
	AcquiringCS.LockCounter++;
}
