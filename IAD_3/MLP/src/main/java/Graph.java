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
    public static void drawPlot(List<Double> errors, int run) {
        double x = 0;
        XYSeries series = new XYSeries("");

        for (int i = 0; i < errors.size(); i++) {
            series.add(x, errors.get(i));
            x++;
        }
        XYSeriesCollection content = new XYSeriesCollection();
        content.addSeries(series);
        JFreeChart chart = ChartFactory.createXYLineChart("Wykres zależnosci wartości błędu od ilości iteracji", "Ilość iteracji", "Wartość błędu", content, PlotOrientation.VERTICAL, true, true, false);
        chart.getXYPlot().setDomainGridlinePaint(Color.blue);
        chart.getXYPlot().setRangeGridlinePaint(Color.blue);
        XYItemRenderer renderer = chart.getXYPlot().getRenderer();
        renderer.setSeriesPaint(0, Color.green);
        try {
            final ChartRenderingInfo descript = new ChartRenderingInfo(new StandardEntityCollection());
            final File graphic = new File("results/graph" + run + ".jpg");
            ChartUtils.saveChartAsJPEG(graphic, chart, 500, 400, descript);

        } catch (Exception e) {}
    }
}
