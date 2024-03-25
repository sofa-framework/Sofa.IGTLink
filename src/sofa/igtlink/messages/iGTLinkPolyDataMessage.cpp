#pragma once

#include "sofa/core/ObjectFactory.h"
#include <sofa/igtlink/messages/iGTLinkPolyDataMessage.h>


using namespace sofa::core::objectmodel;
namespace sofa::openigtlink
{
template<class DataType>
iGTLinkPolyDataMessage<DataType>::iGTLinkPolyDataMessage()
: d_points(initData(&d_points,"points","points"))
, d_indices(initData(&d_indices,"indices","indices"))
, d_edges(initData(&d_edges,"edges","edges"))
, d_triangles(initData(&d_triangles,"triangles","triangles"))
, d_tetra(initData(&d_tetra,"tetra","tetra"))
, d_enableIndices(initData(&d_enableIndices,true,"enableIndices","If false, the indices will not be either packed or unpacked"))
, d_enableEdges(initData(&d_enableEdges,true,"enableEdges","If false, the edges will not be either packed or unpacked"))
, d_enableTriangles(initData(&d_enableTriangles,true,"enableTriangles","If false, the triangles will not be either packed or unpacked"))
, d_enableTetra(initData(&d_enableTetra,false,"enableTetra","If false, the tetra will not be either packed or unpacked"))
, d_enableHexa(initData(&d_enableHexa,false,"enableHexa","If false, the gexa will not be either packed or unpacked"))
{

}


template<class DataType>
igtl::MessageBase::Pointer iGTLinkPolyDataMessage<DataType>::getiGTLinkMessage()
{
    igtl::MessageBase::Pointer polyDataMessage;
    polyDataMessage = igtl::PolyDataMessage::New();

    igtl::PolyDataMessage * polyPtr = static_cast<igtl::PolyDataMessage*>(polyDataMessage.GetPointer());

    polyPtr->InitPack();
    polyDataMessage->SetDeviceName(getName());

    igtl::PolyDataPointArray::Pointer pointArray;
    pointArray = igtl::PolyDataPointArray::New();
    polyPtr->SetPoints(pointArray);
    polyPtr->GetPoints()->SetNumberOfPoints(d_points.getValue().size());

    igtlFloat32 igPoint[3];
    unsigned idx=0;
    for(auto point : d_points.getValue())
    {
        igPoint[0] = (igtlFloat32) point[0];
        igPoint[1] = (igtlFloat32) point[1];
        igPoint[2] = (igtlFloat32) point[2];
        polyPtr->GetPoints()->SetPoint(idx,igPoint);
        ++idx;
    }

    if(d_enableIndices.getValue())
    {
        igtl::PolyDataCellArray::Pointer verticesArray;
        verticesArray = igtl::PolyDataCellArray::New();
        polyPtr->SetVertices(verticesArray);

        igtl::PolyDataCellArray::Cell igCell;
        for(auto indice : d_indices.getValue())
        {
            igCell.push_back(indice);
            verticesArray->AddCell(igCell);
        }
    }

    if(d_enableEdges.getValue())
    {
        igtl::PolyDataCellArray::Pointer edgesArray;
        edgesArray = igtl::PolyDataCellArray::New();
        polyPtr->SetLines(edgesArray);

        igtl::PolyDataCellArray::Cell igCell;
        for(auto edge : d_edges.getValue())
        {
            igCell.push_back(edge[0]);
            igCell.push_back(edge[1]);
            edgesArray->AddCell(igCell);
        }
    }

    if(d_enableTriangles.getValue())
    {
        igtl::PolyDataCellArray::Pointer trianglesArray;
        trianglesArray = igtl::PolyDataCellArray::New();
        polyPtr->SetLines(trianglesArray);

        igtl::PolyDataCellArray::Cell igCell;
        for(auto triangle : d_triangles.getValue())
        {
            igCell.push_back(triangle[0]);
            igCell.push_back(triangle[1]);
            igCell.push_back(triangle[2]);
            trianglesArray->AddCell(igCell);
        }
    }

    if(d_enableTetra.getValue())
    {
        igtl::PolyDataCellArray::Pointer tetraArray;
        tetraArray = igtl::PolyDataCellArray::New();
        polyPtr->SetLines(tetraArray);

        igtl::PolyDataCellArray::Cell igCell;
        for(auto tetra : d_tetra.getValue())
        {
            igCell.push_back(tetra[0]);
            igCell.push_back(tetra[1]);
            igCell.push_back(tetra[2]);
            igCell.push_back(tetra[3]);
            tetraArray->AddCell(igCell);
        }
    }

    if(d_enableHexa.getValue())
    {
        igtl::PolyDataCellArray::Pointer hexaArray;
        hexaArray = igtl::PolyDataCellArray::New();
        polyPtr->SetLines(hexaArray);

        igtl::PolyDataCellArray::Cell igCell;
        for(auto hexa : d_hexa.getValue())
        {
            igCell.push_back(hexa[0]);
            igCell.push_back(hexa[1]);
            igCell.push_back(hexa[2]);
            igCell.push_back(hexa[3]);
            igCell.push_back(hexa[4]);
            igCell.push_back(hexa[5]);
            igCell.push_back(hexa[6]);
            igCell.push_back(hexa[7]);
            hexaArray->AddCell(igCell);
        }
    }

    polyDataMessage->Pack();
    return polyDataMessage;
}

template<class DataType>
void iGTLinkPolyDataMessage<DataType>::updateData(igtl::MessageBase::Pointer message)
{
    igtl::PolyDataMessage * polyPtr = static_cast<igtl::PolyDataMessage*>(message.GetPointer());
    polyPtr->Unpack();

    sofa::helper::WriteAccessor dataPoints(d_points);
    sofa::helper::WriteAccessor dataIndices(d_indices);
    sofa::helper::WriteAccessor dataEdges(d_edges);
    sofa::helper::WriteAccessor dataTriangles(d_triangles);
    sofa::helper::WriteAccessor dataTetra(d_tetra);
    sofa::helper::WriteAccessor dataHexa(d_hexa);


    d_points.beginEdit();
    if(d_enableIndices.getValue())
    {
        d_indices.beginEdit();
        dataIndices.resize(polyPtr->GetVertices()->GetNumberOfCells());
    }
    if(d_enableEdges.getValue())
    {
        d_edges.beginEdit();
        dataEdges.resize(polyPtr->GetLines()->GetNumberOfCells());
    }
    if(d_enableTriangles.getValue())
    {
        d_triangles.beginEdit();
        dataTriangles.resize(polyPtr->GetPolygons()->GetNumberOfCells());
    }
    if(d_enableTetra.getValue())
    {
        d_tetra.beginEdit();
        dataTetra.resize(polyPtr->GetPolygons()->GetNumberOfCells());
    }
    if(d_enableHexa.getValue())
    {
        d_hexa.beginEdit();
        dataHexa.resize(polyPtr->GetPolygons()->GetNumberOfCells());
    }


    dataPoints.resize(polyPtr->GetPoints()->GetNumberOfPoints());
    unsigned idx=0;
    for(auto it = polyPtr->GetPoints()->begin(); it != polyPtr->GetPoints()->end(); ++it, ++idx)
    {
        dataPoints[idx][0] = (*it)[0] ;
        dataPoints[idx][1] = (*it)[1] ;
        dataPoints[idx][2] = (*it)[2] ;
    }
    d_points.endEdit();

    if(d_enableIndices.getValue())
    {
        dataIndices.resize(polyPtr->GetVertices()->GetNumberOfCells());
        unsigned iidx=0;
        for(auto it = polyPtr->GetVertices()->begin(); it != polyPtr->GetVertices()->end(); ++it, ++iidx)
        {
            dataIndices[iidx] = (*(*it).begin());
        }
        d_indices.endEdit();
    }
    if(d_enableEdges.getValue())
    {
        dataEdges.resize(polyPtr->GetLines()->GetNumberOfCells());
        unsigned iidx=0;
        for(auto it = polyPtr->GetLines()->begin(); it != polyPtr->GetLines()->end(); ++it, ++iidx)
        {
            unsigned iidxCell=0;
            for(auto itCell = (*it).begin(); itCell != (*it).end(); ++itCell, ++iidxCell)
            {
                dataEdges[iidx][iidxCell] = (*itCell) ;
            }
        }
        d_edges.endEdit();
    }
    if(d_enableTriangles.getValue())
    {
        dataTriangles.reserve(polyPtr->GetPolygons()->GetNumberOfCells());
        unsigned iidx=0;
        for(auto it = polyPtr->GetPolygons()->begin(); it != polyPtr->GetPolygons()->end(); ++it, ++iidx)
        {
            unsigned iidxCell=0;
            if((*it).size() == 3)
            {
                for (auto itCell = (*it).begin(); itCell != (*it).end(); ++itCell, ++iidxCell)
                {
                    dataTriangles[iidx][iidxCell] = (*itCell);
                }
            }
        }
        d_triangles.endEdit();
    }
    if(d_enableTetra.getValue())
    {
        dataTetra.reserve(polyPtr->GetPolygons()->GetNumberOfCells());
        unsigned iidx=0;
        for(auto it = polyPtr->GetPolygons()->begin(); it != polyPtr->GetPolygons()->end(); ++it, ++iidx)
        {
            unsigned iidxCell=0;
            if((*it).size() == 4)
            {
                for (auto itCell = (*it).begin(); itCell != (*it).end(); ++itCell, ++iidxCell)
                {
                    dataTetra[iidx][iidxCell] = (*itCell);
                }
            }
        }
        d_tetra.endEdit();
    }
    if(d_enableHexa.getValue())
    {
        dataHexa.reserve(polyPtr->GetPolygons()->GetNumberOfCells());
        unsigned iidx=0;
        for(auto it = polyPtr->GetPolygons()->begin(); it != polyPtr->GetPolygons()->end(); ++it, ++iidx)
        {
            unsigned iidxCell=0;
            if((*it).size() == 8)
            {
                for (auto itCell = (*it).begin(); itCell != (*it).end(); ++itCell, ++iidxCell)
                {
                    dataTriangles[iidx][iidxCell] = (*itCell);
                }
            }
        }
        d_hexa.endEdit();
    }
}

static int iGTLinkPolyDataMessageInt = sofa::core::RegisterObject("iGTLink messages")
        .add< iGTLinkPolyDataMessage<sofa::defaulttype::Vec3Types> >();

}
