package eu.jpereira.trainings.designpatterns.creational.builder.xml;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SaleEntry;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

import eu.jpereira.trainings.designpatterns.creational.builder.ReportBodyBuilder;

import java.util.Iterator;

public class XMLReportBodyBuilder implements ReportBodyBuilder {
    private SaleEntry saleEntry;

    @Override
    public void setSaleEntry(SaleEntry saleEntry) {
        this.saleEntry = saleEntry;
    }

    @Override
    public Report buildReport() {
        XMLReportBody reportBody = new XMLReportBody();
        reportBody.putContent("<sale><customer><name>");
        reportBody.putContent(saleEntry.getCustomer().getName());
        reportBody.putContent("</name><phone>");
        reportBody.putContent(saleEntry.getCustomer().getPhone());
        reportBody.putContent("</phone></customer>");
        reportBody.putContent("<items>");

        Iterator<SoldItem> it = saleEntry.getSoldItems().iterator();
        while (it.hasNext()) {
            SoldItem item = it.next();
            reportBody.putContent("<item><name>");
            reportBody.putContent(item.getName());
            reportBody.putContent("</name><quantity>");
            reportBody.putContent(String.valueOf(item.getQuantity()));
            reportBody.putContent("</quantity><price>");
            reportBody.putContent(String.valueOf(item.getUnitPrice()));
            reportBody.putContent("</price></item>");
        }
        reportBody.putContent("</items></sale>");

        Report report = new Report();
        report.setReportBody(reportBody);
        return report;
    }
}