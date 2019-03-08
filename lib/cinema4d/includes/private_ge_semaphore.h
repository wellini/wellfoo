/////////////////////////////////////////////////////////////
// MELANGE SDK                                             //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef PRIVATE_GE_SEMAPHORE_H__
#define PRIVATE_GE_SEMAPHORE_H__

#include "c4d_system.h"
#include "private_ge_thread.h"

namespace melange
{
#pragma pack (push, 8)

#define EnhancedAttemptLock() AttemptLock(__LINE__, __FILE__)
#define EnhancedLock(x)				Lock(x, __LINE__, __FILE__)

class Semaphore
{
private:
	GeRWSpinlock lock;
	Int32				 cnt;
	UInt32			 id;

#ifdef MAXON_TARGET_DEBUG
	Int32	deb_line;
	Char	deb_file[256];
#endif
	void ErrorAlert(void);

public:
	Semaphore(void);
	~Semaphore(void);

	Bool AttemptLock(Int32 line = 0, const Char* file = "");
	Bool Lock(BaseThread* bt, Int32 line = 0, const Char* file = "");

	Int32 UnLock(void);
	void CheckLockCount(void);
	Int32 IsLockedByMe();	// return the lockcount for the own thread
};

class MiniSemaphore
{
private:
	GeSpinlock lock;
	Int32			 cnt;
	UInt32		 id;
	Bool			 writemode;

public:
	MiniSemaphore(void);
	~MiniSemaphore(void);

	void ReadLock(void);
	void ReadUnLock(void);
	void WriteLock(void);
	void WriteUnLock(void);
};

//////////////////////////////////////////////////////////////////////////

class StaticReadLocker
{
private:
	MiniSemaphore* t_ms;

public:
	StaticReadLocker(const MiniSemaphore* ms, Bool protect = true)
	{
		if (!protect)
		{
			t_ms = nullptr;
		}
		else
		{
			t_ms = (MiniSemaphore*)ms;
			t_ms->ReadLock();
		}
	}

	~StaticReadLocker()
	{
		if (t_ms)
			t_ms->ReadUnLock();
	}
};

class StaticWriteLocker
{
private:
	MiniSemaphore* t_ms;

public:
	StaticWriteLocker(const MiniSemaphore* ms, Bool protect = true)
	{
		if (!protect)
		{
			t_ms = nullptr;
		}
		else
		{
			t_ms = (MiniSemaphore*)ms;
			t_ms->WriteLock();
		}
	}

	~StaticWriteLocker()
	{
		if (t_ms)
			t_ms->WriteUnLock();
	}
};

void GeInitSemaphores(void);
void GeEndSemaphores(void);

#pragma pack (pop)
}

#endif	// PRIVATE_GE_SEMAPHORE_H__
