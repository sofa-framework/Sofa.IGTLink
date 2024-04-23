#pragma once

#include <sofa/igtlink/utils/iGTLinkMouseInteractor.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/simulation/AnimateEndEvent.h>
#include <sofa/gui/component/performer/ConstraintAttachBodyPerformer.h>
#include <sofa/gui/component/performer/AttachBodyPerformer.h>
#include <sofa/gui/component/performer/BaseAttachBodyPerformer.inl>
#include <sofa/component/collision/geometry/LineModel.h>
#include <sofa/component/collision/geometry/TriangleModel.h>
#include <sofa/component/collision/geometry/PointModel.h>


namespace sofa::openigtlink
{

template<class DataTypes>
iGTLinkMouseInteractor<DataTypes>::iGTLinkMouseInteractor()
: d_pickingType(initData(&d_pickingType,"pickingType","Mouse interaction type, could be \'constraint\' or \'spring\'"))
, d_positions(initData(&d_positions, "position", "Position"))
, d_springStiffness(initData(&d_springStiffness,10.0,"springStiffness","Stiffness of attachment spring used for interaction"))
, d_reactionTime(initData(&d_reactionTime,20u, "reactionTime", "Time in milisecond of no change in the position to output a null stiffness"))
, l_destCollisionModel(initLink( "destCollisionModel", "Link to the topology to attach"))
, m_performer(nullptr)
, m_performerStarted(false)
{
    sofa::helper::OptionsGroup m_newoptiongroup{"constraint","spring"};
    m_newoptiongroup.setSelectedItem("spring");
    d_pickingType.setValue(m_newoptiongroup);

    this->f_listening.setValue(true);

    c_positions.addInput(&d_positions);
    c_positions.addCallback(std::bind(&iGTLinkMouseInteractor::positionChanged,this));

    c_attachmentType.addInput(&d_pickingType);
    c_attachmentType.addCallback(std::bind(&iGTLinkMouseInteractor::attachmentChanged,this));

    m_lastChange = std::chrono::high_resolution_clock::now();
    //Make sure the constraint is inactive

}


template<class DataTypes>
void iGTLinkMouseInteractor<DataTypes>::positionChanged()
{
    m_lastChange = std::chrono::high_resolution_clock::now();
}

template<class DataTypes>
void iGTLinkMouseInteractor<DataTypes>::attachmentChanged()
{
    if(m_performer)
    {
        m_performer->clear();
    }
    if(d_pickingType.getValue().getSelectedItem() == std::string("constraint"))
    {
        m_performer.reset(new sofa::gui::component::performer::ConstraintAttachBodyPerformer<DataTypes>(this));
    }
    else
    {
        m_performer.reset(new sofa::gui::component::performer::AttachBodyPerformer<DataTypes>(this));
    }
}

template<class DataTypes>
void iGTLinkMouseInteractor<DataTypes>::updatePosition( SReal dt)
{
    SOFA_UNUSED(dt);
    //Do nothing, see handleEvent
}

template<class DataTypes>
void iGTLinkMouseInteractor<DataTypes>::startPerformer()
{
    if(!m_performer || m_performerStarted || !d_positions.getValue().size())
        return;

    sofa::gui::component::performer::BodyPicked bodyPicked;
    bodyPicked.indexCollisionElement = findCollidingElem(d_positions.getValue()[0]);
    bodyPicked.mstate = l_destCollisionModel->getContext()->template get<sofa::core::behavior::BaseMechanicalState>();
    bodyPicked.point = d_positions.getValue()[0];
    bodyPicked.body = l_destCollisionModel.get();
    this->setBodyPicked(bodyPicked);
    this->setMouseAttached(true);

    m_performer->startPartial(bodyPicked);
    m_performer->getInteractionObject()->init();
    m_performer->getInteractionObject()->bwdInit();
    m_performer->getInteractionObject()->f_listening.setValue(true);
    m_performerStarted = true;
}


template<class DataTypes>
void iGTLinkMouseInteractor<DataTypes>::stopPerformer()
{
    if(!m_performer || !m_performerStarted)
        return;
    m_performer->clear();
    this->setMouseAttached(false);

    m_performerStarted = false;
}

template<class DataTypes>
sofa::Index iGTLinkMouseInteractor<DataTypes>::findCollidingElem(const type::Vec3& pos) const
{
    sofa::Index closestElem = l_destCollisionModel->begin().getIndex();
    double closestDist = std::numeric_limits<double>::max();
    auto* topo = l_destCollisionModel->getCollisionTopology();
    auto* mstate = l_destCollisionModel->getContext()->template get<sofa::core::behavior::MechanicalState<DataTypes> >();
    sofa::helper::ReadAccessor<Data <VecCoord> > destPositions = mstate->read(core::VecCoordId::position());

    if(dynamic_cast<sofa::component::collision::geometry::PointCollisionModel<DataTypes>* >(l_destCollisionModel.get()))
    {
        for(unsigned id = 0; id < destPositions.size(); ++id)
        {
            double dist = (pos - destPositions[id]).norm();
            if(dist<closestDist)
            {
                closestDist = dist;
                closestElem = id;
            }
        }
    }
    else if(dynamic_cast<sofa::component::collision::geometry::LineCollisionModel<DataTypes>* >(l_destCollisionModel.get()))
    {
        for(unsigned id = 0; id < topo->getLines().size(); ++id)
        {
            double dist = (pos - (destPositions[topo->getLines()[id][0]] + destPositions[topo->getLines()[id][1]])/2.0).norm();
            if(dist<closestDist)
            {
                closestDist = dist;
                closestElem = id;
            }
        }
    }
    else if(dynamic_cast<sofa::component::collision::geometry::TriangleCollisionModel<DataTypes>* >(l_destCollisionModel.get()))
    {
        for(unsigned id = 0; id < topo->getTriangles().size(); ++id)
        {
            double dist = (pos - (destPositions[topo->getTriangles()[id][0]] + destPositions[topo->getTriangles()[id][1]] + destPositions[topo->getTriangles()[id][2]])/3.0).norm();
            if(dist<closestDist)
            {
                closestDist = dist;
                closestElem = id;
            }
        }
    }
    return closestElem;
}


template<class DataTypes>
void iGTLinkMouseInteractor<DataTypes>::handleEvent(sofa::core::objectmodel::Event *event)
{
    if (dynamic_cast<sofa::simulation::AnimateEndEvent*>(event))
    {
        if(!m_performer)
            attachmentChanged();

        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastChange).count() > d_reactionTime.getValue())
        {
            stopPerformer();
        }
        else
        {
            if(!d_positions.getValue().size())
                return;
            if(!m_performerStarted)
                startPerformer();

            auto* mstate = this->getContext()->template get<sofa::core::behavior::MechanicalState<DataTypes> >();
            sofa::helper::WriteAccessor<Data <defaulttype::Vec3Types::VecCoord> > positions = mstate->write(core::VecCoordId::position());

            mstate->resize(1);

            positions.resize(1);
            positions[0] = d_positions.getValue()[0];
        }
    }
}

}