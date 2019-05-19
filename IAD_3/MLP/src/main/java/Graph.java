import java.awt.*;
import java.io.File;
import java.util.List;

import org.jfree.chart.*;
import org.jfree.chart.entity.StandardEntityCollection;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public class Graph {
    public static void drawPlot(List<Double> list) {
        double x = 0;
        XYSeries series = new XYSeries("");
        for (int i = 0; i < list.size(); i++) {
            series.add(x, list.get(i));
            x++;
        }
        XYSeriesCollection content = new XYSeriesCollection();
        content.addSeries(series);
        JFreeChart chart = ChartFactory.createXYLineChart("Wykres zależnosci wartości błędu od ilości iteracji", "Ilość iteracji", "Wartość błędu", content, PlotOrientation.VERTICAL, true, false, false);
        XYItemRenderer renderer = chart.getXYPlot().getRenderer();
        renderer.setSeriesPaint(0, Color.green);
        try {
            final ChartRenderingInfo description = new ChartRenderingInfo(new StandardEntityCollection());
            final File graphic = new File("results/graph.jpg");
            ChartUtils.saveChartAsJPEG(graphic, chart, 600, 400, description);
        } catch (Exception e) {}
    }
}
