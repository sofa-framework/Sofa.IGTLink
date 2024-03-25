#pragma once

#include <sofa/igtlink/utils/iGTLinkMouseInteractor.h>
#include <sofa/simulation/AnimateBeginEvent.h>


namespace sofa::openigtlink
{

iGTLinkMouseInteractor::iGTLinkMouseInteractor()
: d_pickingType(initData(&d_pickingType,"pickingType","Mouse interaction type, could be \'constraint\' or \'spring\'"))
, d_positions(initData(&d_positions, "position", "Position"))
, d_springStiffness(initData(&d_springStiffness,10.0,"springStiffness","Stiffness of attachment spring used for interaction"))
, d_reactionTime(initData(&d_reactionTime,20u, "reactionTime", "Time in milisecond of no change in the position to output a null stiffness"))
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


void iGTLinkMouseInteractor::positionChanged()
{
    m_lastChange = std::chrono::high_resolution_clock::now();
}

void iGTLinkMouseInteractor::attachmentChanged()
{
    //Change performer
}


void iGTLinkMouseInteractor::updatePosition( SReal dt)
{
    SOFA_UNUSED(dt);
    //Do nothing
}


void iGTLinkMouseInteractor::handleEvent(sofa::core::objectmodel::Event *event)
{
    if (dynamic_cast<sofa::simulation::AnimateBeginEvent*>(event))
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastChange).count() > d_reactionTime.getValue())
        {
            //Deactivate the constraint
            //Reproduce the start emthod from performer here.
        }
        else
        {
            //Activate the constraint
            //Clear the performer
        }
    }
}

}