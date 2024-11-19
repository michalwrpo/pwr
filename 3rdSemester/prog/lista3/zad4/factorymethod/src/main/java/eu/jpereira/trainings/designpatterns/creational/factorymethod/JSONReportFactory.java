package eu.jpereira.trainings.designpatterns.creational.factorymethod;

import eu.jpereira.trainings.designpatterns.creational.factorymethod.Report;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.JSONReport;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.ReportFactory;

public class JSONReportFactory implements ReportFactory {
    @Override
    public Report createReport() {
        return new JSONReport();
    } 
}
