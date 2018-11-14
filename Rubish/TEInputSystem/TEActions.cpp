#include <TEActions.h>

TE::Input::Action::Action()
{

}

TE::Input::Action::~Action()
{

}

TE::Input::AddForceAction::AddForceAction()
{

}

TE::Input::AddForceAction::~AddForceAction()
{

}

void TE::Input::AddForceAction::Execute()
{

}

TE::Input::TransformPositionAction::TransformPositionAction(const Math::Vector3D<Real>& transform)
	:
	m_transform(transform)
{
	
}

TE::Input::TransformPositionAction::~TransformPositionAction()
{

}

void TE::Input::TransformPositionAction::Execute()
{
	
}

TE::Input::TransformOrientationAction::TransformOrientationAction( )
{

}

TE::Input::TransformOrientationAction::~TransformOrientationAction()
{

}


void TE::Input::TransformOrientationAction::Execute()
{

}

TE::Input::TransformScaleAction::TransformScaleAction()
{

}

TE::Input::TransformScaleAction::~TransformScaleAction()
{

}

void TE::Input::TransformScaleAction::Execute()
{

}

