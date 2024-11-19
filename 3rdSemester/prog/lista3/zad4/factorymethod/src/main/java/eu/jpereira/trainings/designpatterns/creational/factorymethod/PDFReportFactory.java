package eu.jpereira.trainings.designpatterns.creational.factorymethod;

import eu.jpereira.trainings.designpatterns.creational.factorymethod.Report;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.PDFReport;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.ReportFactory;

public class PDFReportFactory implements ReportFactory {
    @Override
    public Report createReport() {
        return new PDFReport();
    } 
}
