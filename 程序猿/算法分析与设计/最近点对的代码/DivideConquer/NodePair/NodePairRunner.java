package DivideConquer.NodePair;


import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;

public class NodePairRunner extends ChartPanel {
    private static final long serialVersionUID = 2L;
    public static XYSeries series1;
    public static XYSeries series2;
    public static XYSeries series3;
    public static XYSeries series4;
    static int size = 1000000;
    static int count = 0;
    public NodePairRunner(String chartContent, String title) {
        super(createChart(chartContent, title));
    }

    private static JFreeChart createChart(String chartContent, String title) {
        series1 = new XYSeries(NaiveNodePair.AlgName);
        series2 = new XYSeries(DCNodePair.AlgName);
        series3 = new XYSeries(DCNodePair2.AlgName);
        series4 = new XYSeries(DCNodePair3.AlgName);
        XYSeriesCollection xyDataset = new XYSeriesCollection();
        xyDataset.addSeries(series1);
        xyDataset.addSeries(series2);
        xyDataset.addSeries(series3);
        xyDataset.addSeries(series4);
        JFreeChart jfreechart = ChartFactory.createXYLineChart(title, "顶点个数", "算法耗时(毫秒)", xyDataset);
        ValueAxis valueaxis = jfreechart.getXYPlot().getDomainAxis();
        valueaxis.setAutoRange(true);
        valueaxis.setFixedAutoRange(3000D);
        ((XYPlot) jfreechart.getPlot()).getRenderer(0).setSeriesStroke(0, new BasicStroke(2));
        jfreechart.getXYPlot().getDomainAxis().setRange(0, size);
        return jfreechart;
    }

    private static XYSeriesCollection createDataset() {
        series1.add(0.0, 0.0);
        series2.add(0.0, 0.0);
        series3.add(0.0, 0.0);
        series4.add(0.0, 0.0);
        final XYSeriesCollection dataset = new XYSeriesCollection();
        return dataset;
    }

    public static void main(String[] args) {
        // 设置显示样式，避免中文乱码
        StandardChartTheme standardChartTheme = new StandardChartTheme("CN");
        standardChartTheme.setExtraLargeFont(new Font("微软雅黑", Font.BOLD, 20));
        standardChartTheme.setRegularFont(new Font("微软雅黑", Font.PLAIN, 15));
        standardChartTheme.setLargeFont(new Font("微软雅黑", Font.PLAIN, 15));
        ChartFactory.setChartTheme(standardChartTheme);
        JFrame frame = new JFrame("折线图示例");
        NodePairRunner realTimeChart = new NodePairRunner("算法执行时间示意图", "算法执行时间示意图");
        frame.getContentPane().add(realTimeChart, new BorderLayout().CENTER);
        frame.pack();
        frame.setVisible(true);
        TestRun();
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent windowevent) {
                System.exit(0);
            }
        });
    }

    public static void TestRun() {
        int step = 1000;
        try {
            long startTime = 0;
            long totalTime = 0;
            for (int i = 1000; i <= size; i = i + step) {
                Point[] points = Point.GeneratePairs(i);
//                startTime = System.currentTimeMillis();
//                double r1 = new NaiveNodePair(points).getShortestDistance();
//                totalTime = System.currentTimeMillis() - startTime;
//                series1.add(i, totalTime);

                startTime = System.currentTimeMillis();
                double r2 = new DCNodePair(points).getShortestDistance();
                totalTime = System.currentTimeMillis() - startTime;
                series2.add(i, totalTime);

                startTime = System.currentTimeMillis();
                double r3 = new DCNodePair2(points).getShortestDistance();
                totalTime = System.currentTimeMillis() - startTime;
                series3.add(i, totalTime);

                startTime = System.currentTimeMillis();
                double r4 = new DCNodePair3(points).getShortestDistance();
                totalTime = System.currentTimeMillis() - startTime;
                series4.add(i, totalTime);

                //System.out.println("最近对 " + i + " 距离为" + "\t" + r1 + r2 + "\t" + r3 + "\t" + r4);
            }
        } catch (Exception e) {
            System.out.println(e.toString());
            e.printStackTrace();
        }
    }
}
















