#pragma once

#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/type/Vec.h>
#include <sofa/defaulttype/VecTypes.h>
#include <chrono>

#include <sofa/core/objectmodel/DataCallback.h>
#include <sofa/igtlink/config.h>

using namespace sofa::core::objectmodel;

namespace sofa::openigtlink {

/**
*  \brief This object is used to enable moving the object pre-defined set of
 *  points around with input point data
 *
 *  The input position is only used to activate the spring by setting the output
 *  "outStiffness" to "inStiffness" until no update of the  input is received
 *  for "reactionTime" milliseconds.
 *
 *  This has to be used along a Spring component. The only thing done by this
 *  component is to provide an output stiffness value.
*
 */
class SOFA_IGTLINK_API UserInteractionController : public BaseObject 
{
public :

    typedef sofa::defaulttype::Vec3dTypes::Coord Vec3d;

    SOFA_CLASS(UserInteractionController, BaseObject);

    UserInteractionController();
    void inputChanged();
    void handleEvent(sofa::core::objectmodel::Event *event);


    Data<sofa::type::vector<Vec3d> > d_positions;
    Data<double > d_outStiffness;
    Data<double > d_inStiffness;
    Data<int > d_reactionTime;
    DataCallback c_positions;
    std::chrono::high_resolution_clock::time_point m_lastChange;
};


}
