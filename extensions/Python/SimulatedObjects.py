
def addImplicitHeader(node, iterative=False,_iterations=25,_tolerance=1e-5,_threshold=1e-5):
    node.addObject('EulerImplicitSolver', name='TimeIntegrationSchema')
    if iterative:
        node.addObject('CGLinearSolver', name='LinearSolver', iterations=_iterations, tolerance=_tolerance, threshold=_threshold)

    node.addObject('SparseLDLSolver', name='LinearSolver', template='CompressedRowSparseMatrixd')

    return node

def addTopology(node, elems, type='tetrahedron' ):


    if type=='tetrahedron':
        node.addObject("TetrahedronSetTopologyContainer", name="Container", tetrahedra=elems)
        node.addObject("TetrahedronSetTopologyModifier", name="Modifier")
    elif type=='hexaedron':
        node.addObject("HexahedronSetTopologyContainer", name="Container", hexahedra=elems)
        node.addObject("HexahedronSetTopologyModifier", name="Modifier")

    return node

def addLinearMechanics(node, _restPosition,_youngModulus, _poissonRatio, _totalMass, type='tetrahedron'):

    node.addObject("MechanicalObject", name='mstate',rest_position=_restPosition,template="Vec3d")

    if type=='tetrahedron':
        node.addObject("TetrahedronFEMForceField", name="FEM", youngModulus=_youngModulus, poissonRatio=_poissonRatio, method="large" )
    elif type=='hexaedron':
        node.addObject("HexahedralFEMForceField", name="FEM", youngModulus=_youngModulus, poissonRatio=_poissonRatio, method="large")

    node.addObject("MeshMatrixMass",name="mass", totalMass=_totalMass )

    return node

def addBoundaryConditions(node, ids):
    node.addObject("FixedProjectiveConstraint",name="BoundaryConditions",indices=ids)
    return node

def addLinearTetrahedronNode(node,_name,_restPosition,_elems,_youngModulus, _poissonRatio, _totalMass, _iterative=False,_iterations=25,_tolerance=1e-5,_threshold=1e-5,_fixedPoints=[]):
    tetraNode = node.addChild(_name)

    tetraNode = addImplicitHeader(tetraNode,_iterative,_iterations,_tolerance,_threshold)
    tetraNode = addTopology(tetraNode,_elems)
    tetraNode = addLinearMechanics(tetraNode,_restPosition,_youngModulus, _poissonRatio, _totalMass)

    if(len(_fixedPoints) > 0):
        addBoundaryConditions(tetraNode,_fixedPoints)

    return node