#pragma once
#include <sofa/gui/component/config.h>

#include <sofa/gui/component/performer/InteractionPerformer.h>
#include <sofa/component/collision/geometry/RayModel.h>
#include <sofa/component/statecontainer/MechanicalObject.h>

#include <sofa/core/collision/DetectionOutput.h>
#include <sofa/core/BehaviorModel.h>
#include <sofa/gui/component/performer/MouseInteractor.h>
#include <sofa/helper/OptionsGroup.h>
#include <sofa/core/objectmodel/DataCallback.h>
#include <chrono>


namespace sofa::openigtlink {

class iGTLinkMouseInteractor : public sofa::gui::component::performer::MouseInteractor<defaulttype::Vec3Types> {
public:
    SOFA_CLASS(iGTLinkMouseInteractor, SOFA_TEMPLATE(sofa::gui::component::performer::MouseInteractor, defaulttype::Vec3Types));

    Data<type::Vec3> d_positions;
    Data< sofa::helper::OptionsGroup > d_pickingType;
    Data< double > d_springStiffness;
    Data< unsigned > d_reactionTime;

    iGTLinkMouseInteractor();

    void updatePosition( SReal dt) override;

    void positionChanged();
    void attachmentChanged();
    void handleEvent(sofa::core::objectmodel::Event *event);

private:
    sofa::core::objectmodel::DataCallback c_positions;
    sofa::core::objectmodel::DataCallback c_attachmentType;
    std::chrono::high_resolution_clock::time_point m_lastChange;



};

}