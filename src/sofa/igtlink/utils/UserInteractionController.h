#pragma once

#include <sofa/core/objectmodel/BaseObject.h>
#include <sofa/type/Vec.h>
#include <sofa/defaulttype/VecTypes.h>
#include <chrono>

#include <sofa/core/objectmodel/DataCallback.h>

using namespace sofa::core::objectmodel;

namespace sofa::openigtlink {

class UserInteractionController : public BaseObject {
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
