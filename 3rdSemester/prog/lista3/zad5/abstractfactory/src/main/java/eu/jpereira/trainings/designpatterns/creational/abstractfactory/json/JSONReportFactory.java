package eu.jpereira.trainings.designpatterns.creational.abstractfactory.json;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportHeader;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportHeader;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportFooter;

// implementation for abstract factory
public class JSONReportFactory implements ReportFactory {
    @Override
    public ReportBody getReportBody() {
        return new JSONReportBody();
    } 

    public ReportHeader getReportHeader() {
        return new JSONReportHeader();
    }

    public ReportFooter getReportFooter() {
        return new JSONReportFooter();
    }
}
