#pragma once

#include <sofa/igtlink/utils/EngineToMState.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/type/Quat.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/component/statecontainer/MechanicalObject.h>




namespace sofa::openigtlink {

using namespace core::behavior;
using namespace sofa::type;
using namespace sofa::defaulttype;

template<class DataTypes>
EngineToMState<DataTypes>::EngineToMState()
: d_positions(initData(&d_positions, "position", "Position"))
, d_scale(initData(&d_scale,1.0, "scale", "scale"))
, d_eachStep(initData(&d_eachStep,false, "eachStep", "scale"))
, l_state(initLink("state", "Link to state"))
{
    this->f_listening.setValue(true);

    c_positions.addInput(&d_positions);
    c_positions.addCallback(std::bind(&EngineToMState<DataTypes>::inputChanged,this));

    l_state.setPath("@.");
}

template<class DataTypes>
void EngineToMState<DataTypes>::inputChanged()
{
   if(d_eachStep.getValue())
   {
     m_isDirty=true;
     return;
   }
   else
   {
     applyTopologyChanges();
     return;
   }
};


template<class DataTypes>
void EngineToMState<DataTypes>::applyTopologyChanges() {
    if (l_state == NULL) return;
    if (!this->getContext()->isActive()) return;

    helper::WriteAccessor<Data <VecCoord> > X = *l_state->write(core::VecCoordId::position());
    helper::WriteAccessor<Data <VecCoord> > Xfree = *l_state->write(core::VecCoordId::freePosition());
    helper::WriteAccessor<Data <VecCoord> > X0 = *l_state->write(core::VecCoordId::restPosition());

    l_state->resize(d_positions.getValue().size());

    X.resize(d_positions.getValue().size());
    Xfree.resize(d_positions.getValue().size());
    X0.resize(d_positions.getValue().size());

    for(unsigned i = 0; i < d_positions.getValue().size() ; i++){
        X[i] = d_positions.getValue()[i]*d_scale.getValue();
        Xfree[i] = d_positions.getValue()[i]*d_scale.getValue();
        X0[i] = d_positions.getValue()[i]*d_scale.getValue();
    }
    m_isDirty = false;
}

template<class DataTypes>
void EngineToMState<DataTypes>::handleEvent(sofa::core::objectmodel::Event *event)
{
    if (dynamic_cast<sofa::simulation::AnimateBeginEvent*>(event))
    {
      if(d_eachStep.getValue() && m_isDirty)
        applyTopologyChanges();
    }

}


}
