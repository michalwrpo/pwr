package eu.jpereira.trainings.designpatterns.creational.builder.json;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SaleEntry;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SoldItem;

import eu.jpereira.trainings.designpatterns.creational.builder.ReportBodyBuilder;

import java.util.Iterator;

public class JSONReportBodyBuilder implements ReportBodyBuilder {
    private SaleEntry saleEntry;

    @Override
    public void setSaleEntry(SaleEntry saleEntry) {
        this.saleEntry = saleEntry;
    }

    @Override
    public Report buildReport() {
        JSONReportBody reportBody = new JSONReportBody();

        reportBody.addContent("sale:{customer:{");
        reportBody.addContent("name:\"");
        reportBody.addContent(saleEntry.getCustomer().getName());
        reportBody.addContent("\",phone:\"");
        reportBody.addContent(saleEntry.getCustomer().getPhone());
        reportBody.addContent("\"},items:[");

        Iterator<SoldItem> it = saleEntry.getSoldItems().iterator();
        while (it.hasNext()) {
            SoldItem item = it.next();
            reportBody.addContent("{name:\"");
            reportBody.addContent(item.getName());
            reportBody.addContent("\",quantity:");
            reportBody.addContent(String.valueOf(item.getQuantity()));
            reportBody.addContent(",price:");
            reportBody.addContent(String.valueOf(item.getUnitPrice()));
            reportBody.addContent("}");
            if (it.hasNext()) {
                reportBody.addContent(",");
            }
        }
        reportBody.addContent("]}");

        Report report = new Report();
        report.setReportBody(reportBody);
        return report;
    }
}