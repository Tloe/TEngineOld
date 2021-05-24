#include <TEGlobalState.h>

std::unique_ptr<TE::SceneGraph::GlobalState>
    TE::SceneGraph::GlobalState::s_default[TE::SceneGraph::GlobalState::STATE_COUNT];
