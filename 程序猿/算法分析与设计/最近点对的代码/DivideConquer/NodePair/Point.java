package DivideConquer.NodePair;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;

public class Point {
    public double x;
    public double y;

    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public static double Dis(Point p1, Point p2) {
        return Math.sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
    }

    public static Point[] GeneratePairs(int size){
        Random r = new Random();
        Point[] points = new Point[size];
        for(int i = 0; i < points.length; i++) {
            points[i] = new Point(r.nextDouble() * 100000.00, r.nextDouble() * 100000.00);
        }
        Arrays.sort(points, new Comparator<Point>() {
            @Override
            public int compare(Point p1, Point p2) {
                return (p1.x > p2.x) ? 1 : (p1.x == p2.x) ? 0 : -1;
            }
        });
        return points;
    }
}
