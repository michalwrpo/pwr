package eu.jpereira.trainings.designpatterns.creational.factorymethod;

import eu.jpereira.trainings.designpatterns.creational.factorymethod.Report;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.XMLReport;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.ReportFactory;

public class XMLReportFactory implements ReportFactory {
    @Override
    public Report createReport() {
        return new XMLReport();
    } 
}
