package DivideConquer.NodePair;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class DCNodePair3 extends DCNodePair{
    public static final String AlgName = "分治法（不带排序）";
    public DCNodePair3(Point[] p){
        super(p);
    }
    @Override
    protected double merge(int left, int right, int middle, double MinDis){
        ArrayList<Integer> validPointIndex = new ArrayList<Integer>();
        for (int i = left; i <= right; i++) {
            if (Math.abs(points[middle].x - points[i].x) <= MinDis) {
                validPointIndex.add(i);
            }
        }
        // 基于索引，进一步计算区间内最小两点距离
        double dl = Double.MAX_VALUE;
        for (int i = 0; i < validPointIndex.size() - 1; i++) {
            for (int j = i + 1; j < validPointIndex.size(); j++) {
                //筛选
                if (Math.abs(points[validPointIndex.get(i)].y - points[validPointIndex.get(j)].y) > MinDis) {
                    continue;
                }
                double tempDis = Point.Dis(points[validPointIndex.get(i)], points[validPointIndex.get(j)]);
                dl = (tempDis < dl) ? tempDis : dl;
            }
        }
        return dl;
    }
}
