#pragma once

#include <sofa/type/Mat.h>
#include <sofa/defaulttype/RigidTypes.h>
#include <sofa/type/Vec.h>
#include <sofa/defaulttype/VecTypes.h>

#include <sofa/core/objectmodel/Event.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/simulation/AnimateEndEvent.h>
#include <sofa/core/objectmodel/KeypressedEvent.h>
#include <sofa/core/objectmodel/KeyreleasedEvent.h>

#include <sofa/component/topology/container/dynamic/PointSetTopologyContainer.h>
#include <sofa/component/topology/container/dynamic/PointSetTopologyModifier.h>
#include <sofa/core/topology/TopologyChange.h>
#include <sofa/core/topology/TopologyData.h>
#include <sofa/core/topology/TopologicalMapping.h>

#include <sofa/core/visual/VisualParams.h>
#include <sofa/core/behavior/MechanicalState.h>
#include <sofa/core/objectmodel/DataCallback.h>

namespace sofa {

namespace registrationcst {

template<class DataTypes>
class EngineToTopology : public core::objectmodel::BaseObject {
public :

    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;

    typedef sofa::component::topology::container::dynamic::PointSetTopologyContainer PointTopologyContainer;
    typedef sofa::component::topology::container::dynamic::PointSetTopologyModifier PointTopologyModifier;

    SOFA_CLASS(SOFA_TEMPLATE(EngineToTopology, DataTypes), core::objectmodel::BaseObject);

    Data<sofa::type::vector<Coord> > d_positions;
    Data<double > d_scale;
    Data<bool > d_eachStep;
    core::objectmodel::DataCallback c_positions;
    core::objectmodel::SingleLink<EngineToTopology<DataTypes>,sofa::core::behavior::MechanicalState<DataTypes>,BaseLink::FLAG_STRONGLINK|BaseLink::FLAG_STOREPATH> l_state;

    EngineToTopology();

    void applyTopologyChanges();
    void inputChanged();
    void handleEvent(sofa::core::objectmodel::Event *event);

    bool m_isDirty;

    static std::string templateName(const EngineToTopology<DataTypes>* = nullptr) { return "Vec3d"; }
};

}

}
