package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportHeader;

// abstract factory
public interface ReportFactory {
    ReportBody getReportBody();
    ReportHeader getReportHeader();
    ReportFooter getReportFooter();
} 
