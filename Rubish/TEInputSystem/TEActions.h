#ifndef TEACTIONS_H
#define TEACTIONS_H

#include <memory>
#include <string>
#include "TEDataTypes.h"
#include "TEVector3D.h"

namespace TE
{
	namespace Input
	{
		namespace ActionType
		{
			enum
			{
				AddforceAction,
				TransformPositionAction,
				TransformOrientationAction,
				TransformScaleAction
			};
		}

		class Action
		{
		public:
			Action();
			virtual ~Action();

			virtual void Execute() = 0;
		};

		typedef std::unique_ptr<Action> ActionUPtr;

		class AddForceAction : public Action
		{
		public:
			AddForceAction();
			virtual ~AddForceAction();

			virtual void Execute();
		};

		class TransformPositionAction : public Action
		{
		public:
			TransformPositionAction(const Math::Vector3D<Real>& transform);
			virtual ~TransformPositionAction();

			virtual void Execute();
		private:
			Math::Vector3D<Real> m_transform;
		};

		class TransformOrientationAction : public Action
		{
		public:
			TransformOrientationAction();
			virtual ~TransformOrientationAction();
			virtual void Execute();
		};
		
		class TransformScaleAction : public Action
		{
		public:
			TransformScaleAction();
			virtual ~TransformScaleAction();

			virtual void Execute();
		};
	}
}

#endif