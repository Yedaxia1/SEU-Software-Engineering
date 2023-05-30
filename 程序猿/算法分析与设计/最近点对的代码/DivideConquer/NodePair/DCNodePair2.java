package DivideConquer.NodePair;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class DCNodePair2 extends NodePairBase{
    public static final String AlgName = "分治法（带预处理）";
    private Integer[] yIndexAll;
    public DCNodePair2(Point[] p){
        super(p);
        yIndexAll = getYSortedIndex();
    }
    private Integer[] getYSortedIndex(){
        Integer[] index = new Integer[points.length];
        for(int i= 0;i<index.length; i++) index[i] = i;
        Arrays.sort(index, new Comparator<Integer>() {
            @Override
            public int compare(Integer p1, Integer p2) {
                return (points[p1].y > points[p2].y) ? 1 : (points[p1].y == points[p2].y) ? 0 : -1;
            }
        });
        return index;
    }

    public double getShortestDistance() {
        return NearPair(0, points.length-1, yIndexAll);
    }
    protected double NearPair(int left, int right, Integer[] yIndex) {
        double MinDis = Double.MAX_VALUE;
        // 只有一个点，不存在最近两点距离，返回无穷大
        if (left >= right) {
            return MinDis;
        }
        // 只有两个点，直接求解。
        if (left + 1 == right) {
            return Point.Dis(points[left], points[right]);
        }
        //分治
        int middle = (left + right) / 2;

        Integer[] yIndexLeft = new Integer[middle-left];
        Integer[] yIndexRight = new Integer[right-middle+1];
        int leftCursor = 0;
        int rightCursor = 0;
        for(int i=0; i<yIndex.length; i++){
            if(yIndex[i] < middle) yIndexLeft[leftCursor++]=yIndex[i];
            else yIndexRight[rightCursor++]=yIndex[i];
        }

        double leftMinDis = NearPair(left, middle-1,yIndexLeft);
        double rightMinDis = NearPair(middle, right,yIndexRight);
        MinDis = (leftMinDis <= rightMinDis) ? leftMinDis : rightMinDis;
        //合并
        double dl = merge(left, right, middle, MinDis, yIndex);
        return (dl < MinDis) ? dl : MinDis;
    }

    protected double merge(int left, int right, int middle, double MinDis, Integer[] yIndex){
        ArrayList<Integer> validPointIndex = new ArrayList<Integer>();
        for(int i=0; i<yIndex.length; i++){
            if(Math.abs(points[middle].x - points[yIndex[i]].x) <= MinDis){
                validPointIndex.add(yIndex[i]);
            }
        }
        double dl = Double.MAX_VALUE;
        for(int i=0; i<validPointIndex.size(); i++){
            if(validPointIndex.get(i) < middle && Math.abs(points[middle].x - points[validPointIndex.get(i)].x) <= MinDis){
                for(int j=i-1; j>=0; j--){
                    if (Math.abs(points[validPointIndex.get(i)].y - points[validPointIndex.get(j)].y) > MinDis) {
                        break;
                    }
                    double tempDis = Point.Dis(points[validPointIndex.get(i)], points[validPointIndex.get(j)]);
                    dl = (tempDis < dl) ? tempDis : dl;
                    if(dl == 0 )
                        System.out.println("Error");
                }
                for(int j=i+1; j<validPointIndex.size(); j++){
                    if (Math.abs(points[validPointIndex.get(i)].y - points[validPointIndex.get(j)].y) > MinDis) {
                        break;
                    }
                    double tempDis = Point.Dis(points[validPointIndex.get(i)], points[validPointIndex.get(j)]);
                    dl = (tempDis < dl) ? tempDis : dl;
                    if(dl == 0 )
                        System.out.println("Error");
                }
            }
        }
        return dl;
    }
}
