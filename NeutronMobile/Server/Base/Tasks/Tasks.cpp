#define __COMPILING_NS_TASKS_CPP__
#include "Tasks.h"
#undef __COMPILING_NS_TASKS_CPP__
 
#include "../Assert/Assert.h"
#include "Task.h"

using namespace Ns;


Tasks::Tasks()
{
}

Tasks::~Tasks()
{
}

Tasks* Tasks::make()
{
	return new Tasks();
}

void Tasks::destroy()
{
	delete this;
}

void Tasks::add(Task* task)
{
	m_queue.push_back(task);
}

void Tasks::executeOne()
{
	TaskQueue::iterator itr = m_queue.begin();
	if (itr == m_queue.end())
		return;

	Task* pTask = (*itr);
	m_queue.erase(itr);

	bool bCompleted = pTask->execute();

	if (!bCompleted)
		this->add(pTask);
	else
		pTask->destroy();
}

void Tasks::executeAll()
{
	size_t nInitialSize = m_queue.size();
	for (size_t i = 0; i < nInitialSize; i++)
	{
		this->executeOne();
	}
}

Ns::IString Tasks::toString() const
{
    Ns::IString str;
    return str;
}
