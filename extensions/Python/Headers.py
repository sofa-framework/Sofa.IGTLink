
def addDefaultHeader(node):

    node.addObject('VisualStyle', displayFlags="showBehaviorModels showForceFields")

    node.addObject("RequiredPlugin", pluginName=['Sofa.Component.Constraint.Projective',
                                                 'Sofa.Component.Engine.Select',
                                                 'Sofa.Component.LinearSolver.Direct',
                                                 'Sofa.Component.Mass',
                                                 'Sofa.Component.ODESolver.Backward',
                                                 'Sofa.Component.SolidMechanics.FEM.Elastic',
                                                 'Sofa.Component.StateContainer',
                                                 'Sofa.Component.Topology.Container.Grid',
                                                 ])
    node.addObject('DefaultAnimationLoop')

    return node


def addContactHeader(node,alarmDistance, contactDistance, frictionCoef=0.0):

    node.addObject("RequiredPlugin", pluginName=['Sofa.Component.Constraint.Lagrangian',
                                                 'Sofa.Component.Constraint.Projective',
                                                 'Sofa.Component.Engine.Select',
                                                 'Sofa.Component.LinearSolver.Direct',
                                                 'Sofa.Component.Mass',
                                                 'Sofa.Component.ODESolver.Backward',
                                                 'Sofa.Component.SolidMechanics.FEM.Elastic',
                                                 'Sofa.Component.StateContainer',
                                                 'Sofa.Component.Topology.Container.Grid',
                                                 ])

    node.addObject('CollisionPipeline')

    node.addObject('BruteForceBroadPhase')
    node.addObject('BVHNarrowPhase')

    node.addObject('RuleBasedContactManager', responseParams="mu="+str(frictionCoef),
                      name='Response', response='FrictionContactConstraint')
    node.addObject('LocalMinDistance',
                      alarmDistance=alarmDistance, contactDistance=contactDistance,
                      angleCone=0.01)
    node.addObject('FreeMotionAnimationLoop')

    node.addObject('GenericConstraintSolver', tolerance=1e-6, maxIterations=1000)

    return node