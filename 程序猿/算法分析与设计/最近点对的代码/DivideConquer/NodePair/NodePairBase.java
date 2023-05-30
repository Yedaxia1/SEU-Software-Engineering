package DivideConquer.NodePair;


public abstract class NodePairBase {
    protected final Point[] points;
    public NodePairBase(Point[] p){
        points = p;
    }

    abstract public double getShortestDistance();
}




