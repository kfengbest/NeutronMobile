#pragma once
 
// ------------------------------------------------------------
// Task is a base class that represents an independent unit
// of work that can be done.  Ideally any derived class can
// be executed in parallel on multiple threads.  Right now there
// is not any dependency information modeled on a Task, but 
// that will come on later so that the necessary ordering
// of tasks is represented when multithreaded.
// ------------------------------------------------------------

#include "../Globals.h"

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_TASK_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {

	class NS_BASE_API Task 
	{
	protected:
		Task();
		virtual ~Task();

	public:
		// Returns true if the task is completed and it can be removed
		// Returns false if the task has additional work to do and should
		// remain in the queue and be called again at the next opportunistic
		// time.  
		void destroy();
		bool execute();
		Ns::IString toString() const;

	protected:
		virtual void onDestroy();
		virtual bool onExecute() = 0;
		virtual Ns::IString onToString() const;
	};
}


#undef NS_BASE_API


