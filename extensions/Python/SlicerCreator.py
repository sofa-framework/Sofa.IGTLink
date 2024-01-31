import Sofa
import SofaRuntime
import Headers as headers
import SimulatedObjects as so

def createScene(root):

    root = headers.addDefaultHeader(root)
    root = so.addLinearTetrahedronNode()

    return root



