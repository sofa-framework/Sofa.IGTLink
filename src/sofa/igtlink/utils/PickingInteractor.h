#pragma once
#include <sofa/gui/component/config.h>

#include <sofa/gui/component/performer/InteractionPerformer.h>
#include <sofa/gui/component/performer/BaseAttachBodyPerformer.h>
#include <sofa/component/collision/geometry/RayModel.h>
#include <sofa/component/statecontainer/MechanicalObject.h>

#include <sofa/core/collision/DetectionOutput.h>
#include <sofa/core/BehaviorModel.h>
#include <sofa/gui/component/performer/MouseInteractor.h>
#include <sofa/gui/component/AttachBodyButtonSetting.h>
#include <sofa/helper/OptionsGroup.h>
#include <sofa/core/objectmodel/DataCallback.h>
#include <sofa/core/CollisionModel.h>
#include <chrono>
#include <sofa/igtlink/config.h>


namespace sofa::openigtlink {

/**
*  \brief This object is used to enable random picking of an object using either
 *  lagrangian multipliers or springs.
 *
 *  The input position is used to find the closest point on the collision model
 *  (link "destCollisionModel").
 *  This closest point is then used to attach the object to the input point.
 *  This interaction is active and follows the input without updating the
 *  projection on the surface until no update of the input is received for
 *  "reactionTime" milliseconds.
 *
 *  When "reactionTime" milliseconds has passed without an update of the input,
 *  the interaction is deactivated and next time the input is updated, a new
 *  closest point will be found to attach the object
*
 */
template<class DataTypes>
class SOFA_IGTLINK_API PickingInteractor : public sofa::gui::component::performer::MouseInteractor<DataTypes> {
public:
    SOFA_CLASS(SOFA_TEMPLATE(PickingInteractor,DataTypes), SOFA_TEMPLATE(sofa::gui::component::performer::MouseInteractor,DataTypes));

    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;


    Data<sofa::type::vector<Coord> > d_positions;
    Data< sofa::helper::OptionsGroup > d_pickingType;
    Data< double > d_springStiffness;
    Data< unsigned > d_reactionTime;

    SingleLink<PickingInteractor, core::CollisionModel, BaseLink::FLAG_STOREPATH | BaseLink::FLAG_STRONGLINK> l_destCollisionModel;


    PickingInteractor();

    virtual void updatePosition( SReal dt) override;

    void positionChanged();
    void attachmentChanged();
    void startPerformer();
    void stopPerformer();
    void handleEvent(sofa::core::objectmodel::Event *event);
    sofa::Index findCollidingElem(const type::Vec3& pos) const;


private:
    sofa::core::objectmodel::DataCallback c_positions;
    sofa::core::objectmodel::DataCallback c_attachmentType;
    std::chrono::high_resolution_clock::time_point m_lastChange;
    std::unique_ptr<sofa::gui::component::performer::BaseAttachBodyPerformer<DataTypes>> m_performer;

    bool m_performerStarted;



};

}