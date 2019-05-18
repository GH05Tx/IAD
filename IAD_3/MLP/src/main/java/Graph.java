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
        double x=0;
        XYSeries series = new XYSeries("");

        for(int i=0; i<errors.size(); i++) {
            series.add(x, errors.get(i));
            x++;
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        JFreeChart chart = ChartFactory.createXYLineChart("", "Ilość iteracji", "Wartość błędu", dataset, PlotOrientation.VERTICAL,true,true,false);
        chart.setBackgroundPaint(Color.white);
        chart.getPlot().setBackgroundPaint(Color.white);
        chart.getXYPlot().setDomainGridlinePaint(Color.lightGray);
        chart.getXYPlot().setRangeGridlinePaint(Color.lightGray);
        XYItemRenderer renderer = chart.getXYPlot().getRenderer();
        renderer.setSeriesPaint(0,Color.BLUE);
        chart.setTitle("MLP Error Chart");
        try {
            final ChartRenderingInfo info = new ChartRenderingInfo(new StandardEntityCollection());
            final File file1 = new File("data/test"+run+".png");
            ChartUtils.saveChartAsPNG(file1,chart,500,450,info);

        }catch (Exception e){

        }
    }
}
