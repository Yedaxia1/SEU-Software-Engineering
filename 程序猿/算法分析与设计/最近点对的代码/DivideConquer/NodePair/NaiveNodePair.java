package DivideConquer.NodePair;

public class NaiveNodePair extends NodePairBase{
    public static final String AlgName = "暴力求解法";
    public NaiveNodePair(Point[] p){
        super(p);
    }
    public double getShortestDistance() {
        double MinDis = Double.MAX_VALUE;
        for (int i = 0; i < points.length-1; i++) {
            for (int j = i + 1; j < points.length-1; j++) {
                double tempDis = Point.Dis(points[i], points[j]);
                MinDis = (tempDis < MinDis) ? tempDis : MinDis;
            }
        }
        return MinDis;
    }
}
