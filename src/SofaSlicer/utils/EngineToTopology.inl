#pragma once

#include <SofaSlicer/utils/EngineToTopology.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/type/Quat.h>
#include <sofa/core/ObjectFactory.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/component/statecontainer/MechanicalObject.h>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <sofa/helper/AdvancedTimer.h>

namespace sofa {

namespace registrationcst {

using namespace core::behavior;
using namespace sofa::type;
using namespace sofa::defaulttype;
using namespace sofa::component::topology;
using namespace sofa::core::topology;

template<class DataTypes>
EngineToTopology<DataTypes>::EngineToTopology()
: d_positions(initData(&d_positions, "position", "Position"))
, d_scale(initData(&d_scale,1.0, "scale", "scale"))
, d_eachStep(initData(&d_eachStep,false, "eachStep", "scale"))
, l_state(initLink("state", "Link to state"))
{
    this->f_listening.setValue(true);

    c_positions.addInput(&d_positions);
    c_positions.addCallback(std::bind(&EngineToTopology<DataTypes>::inputChanged,this));

    l_state.setPath("@.");
}

template<class DataTypes>
void EngineToTopology<DataTypes>::inputChanged()
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
void EngineToTopology<DataTypes>::applyTopologyChanges() {
    if (l_state == NULL) return;
    if (!this->getContext()->isActive()) return;

    helper::WriteAccessor<Data <VecCoord> > X = *l_state->write(core::VecCoordId::position());
    helper::WriteAccessor<Data <VecCoord> > Xfree = *l_state->write(core::VecCoordId::freePosition());
    helper::WriteAccessor<Data <VecCoord> > X0 = *l_state->write(core::VecCoordId::restPosition());

    l_state->resize(d_positions.getValue().size());

//    if(d_positions.getValue().size() > X.size()){
//        int nb = d_positions.getValue().size() - X.size();

//        l_modifier->addPointsProcess(nb);
//        l_modifier->addPointsWarning(nb);
//        l_modifier->propagateTopologicalChanges();
//    } else if(X.size() > d_positions.getValue().size()){
//        int nb = X.size() - d_positions.getValue().size();

//        sofa::type::vector<unsigned int> indices;
//        for(int i = 0; i < nb ; ++i) indices.push_back(d_positions.getValue().size() + i);

//        l_modifier->removePointsWarning(indices, true);
//        l_modifier->propagateTopologicalChanges();
//        l_modifier->removePointsProcess(indices, true);
//    }

    X.resize(d_positions.getValue().size());
    Xfree.resize(d_positions.getValue().size());
    X0.resize(d_positions.getValue().size());

    for(unsigned i = 0; i < d_positions.getValue().size() ; i++){
        X[i] = d_positions.getValue()[i]*d_scale.getValue();
        Xfree[i] = d_positions.getValue()[i]*d_scale.getValue();
        X0[i] = d_positions.getValue()[i]*d_scale.getValue();
    }

//    l_modifier->addPointsProcess(0);
//    l_modifier->addPointsWarning(0);
//    l_modifier->propagateTopologicalChanges();
    m_isDirty = false;
}

template<class DataTypes>
void EngineToTopology<DataTypes>::handleEvent(sofa::core::objectmodel::Event *event)
{
    if (dynamic_cast<sofa::simulation::AnimateBeginEvent*>(event))
    {
      if(d_eachStep.getValue() && m_isDirty)
        applyTopologyChanges();
    }

}

}
}
