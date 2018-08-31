#pragma once
 
// ------------------------------------------------------------
// Tasks is a simple collection of Task objects.  It provides
// an easy way to collect tasks and execute them using a variety
// of different methods (i.e. synchronously, asynchronously or
// even on multiple threads at some point).
// ------------------------------------------------------------

#include "../Globals.h"
#include <vector>

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_TASKS_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {

	class Task;

	class NS_BASE_API Tasks
	{
	private:
		Tasks();
		virtual ~Tasks();

	public:
		static Tasks* make();

		void destroy();
		void add(Task* task);
		void executeOne();
		void executeAll();
		Ns::IString toString() const;

	private:
		typedef std::vector<Task*> TaskQueue;
		TaskQueue m_queue;
	};
}


#undef NS_BASE_API


