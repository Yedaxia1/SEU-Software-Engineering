package DivideConquer.NodePair;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class DCNodePair extends NodePairBase {
    public static final String AlgName = "分治法（不带预处理）";
    public DCNodePair(Point[] p){
        super(p);
    }
    public double getShortestDistance() {
        return NearPair(0, points.length-1);
    }
    protected double NearPair(int left, int right) {
        double MinDis = Double.MAX_VALUE;
        // 只有一个点，不存在最近两点距离，返回无穷大
        if (left == right) {
            return MinDis;
        }
        // 只有两个点，直接求解。
        if (left + 1 == right) {
            return Point.Dis(points[left], points[right]);
        }
        //分治
        int middle = (left + right) / 2;
        double leftMinDis = NearPair(left, middle);
        double rightMinDis = NearPair(middle, right);
        MinDis = (leftMinDis <= rightMinDis) ? leftMinDis : rightMinDis;
        //合并
        double dl = merge(left, right, middle, MinDis);
        return (dl < MinDis) ? dl : MinDis;
    }

    protected double merge(int left, int right, int middle, double MinDis){
        ArrayList<Integer> validPointIndex = new ArrayList<Integer>();
        for (int i = left; i <= right; i++) {
            if (Math.abs(points[middle].x - points[i].x) <= MinDis) {
                validPointIndex.add(i);
            }
        }
        Integer[] validPoints = validPointIndex.toArray(new Integer[validPointIndex.size()]);
        Arrays.sort(validPoints, new Comparator<Integer>() {
            @Override
            public int compare(Integer p1, Integer p2) {
                return (points[p1].y > points[p2].y) ? 1 : (points[p1].y == points[p2].y) ? 0 : -1;
            }
        });

        double dl = Double.MAX_VALUE;
        for(int i=0; i<validPoints.length; i++){
            if(validPoints[i] < middle && Math.abs(points[middle].x - points[validPoints[i]].x) <= MinDis){
                for(int j=i-1; j>=0; j--){
                    if (Math.abs(points[validPoints[i]].y - points[validPoints[j]].y) > MinDis) {
                        break;
                    }
                    double tempDis = Point.Dis(points[validPoints[i]], points[validPoints[j]]);
                    dl = (tempDis < dl) ? tempDis : dl;
                }
                for(int j=i+1; j<validPoints.length; j++){
                    if (Math.abs(points[validPoints[i]].y - points[validPoints[j]].y) > MinDis) {
                        break;
                    }
                    double tempDis = Point.Dis(points[validPoints[i]], points[validPoints[j]]);
                    dl = (tempDis < dl) ? tempDis : dl;
                }
            }
        }
        return dl;
    }
}
