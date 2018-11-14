#ifndef TESUBJECTVISITORS_H
#define TESUBJECTVISITORS_H

#include <assert.h>

namespace TE
{
	namespace Engine { class TransformChange; }

	namespace Engine
	{
		class SubjectVisitor
		{
		public:
			virtual void Visit(TransformChange & transformInterface) { assert(false); }
		};

		template <class ChangeInterface>
		class ChangeVisitor : public SubjectVisitor
		{
		public:
			virtual void Visit(ChangeInterface & changeInterface) { m_changeInterface = &changeInterface; }
		
			ChangeInterface* GetChangeInterface() { return m_changeInterface; }
		private:
			ChangeInterface* m_changeInterface;
		};
	}
}

#endif