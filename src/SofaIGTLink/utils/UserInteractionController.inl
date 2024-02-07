#pragma once

#include <SofaIGTLink/utils/UserInteractionController.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/type/Quat.h>
#include <sofa/core/ObjectFactory.h>
#include <sofa/simulation/AnimateBeginEvent.h>
#include <sofa/component/statecontainer/MechanicalObject.h>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <sofa/helper/AdvancedTimer.h>

namespace SofaSlicer {


UserInteractionController::UserInteractionController()
: d_positions(initData(&d_positions, "position", "Position"))
, d_outStiffness(initData(&d_outStiffness, "outStiffness", "Position"))
, d_inStiffness(initData(&d_inStiffness, "inStiffness", "Position"))
, d_reactionTime(initData(&d_reactionTime,20, "reactionTime", "Time in milisecond of no change in the position to output a null stiffness"))
{
    this->f_listening.setValue(true);

    c_positions.addInput(&d_positions);
    c_positions.addCallback(std::bind(&UserInteractionController::inputChanged,this));

    m_lastChange = std::chrono::high_resolution_clock::now();
    d_outStiffness.setValue(0);
}


void UserInteractionController::inputChanged()
{
    m_lastChange = std::chrono::high_resolution_clock::now();
}

void UserInteractionController::handleEvent(sofa::core::objectmodel::Event *event)
{
    if (dynamic_cast<sofa::simulation::AnimateBeginEvent*>(event))
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastChange).count() > d_reactionTime.getValue())
        {
            d_outStiffness.setValue(0);
        }
        else
        {
            d_outStiffness.setValue(d_inStiffness.getValue());
        }
    }
}


}
