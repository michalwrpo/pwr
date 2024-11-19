package eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFooter;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportHeader;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportBody;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportHeader;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportFooter;

// implementation for abstract factory
public class XMLReportFactory implements ReportFactory {
    @Override
    public ReportBody getReportBody() {
        return new XMLReportBody();
    } 

    public ReportHeader getReportHeader() {
        return new XMLReportHeader();
    }

    public ReportFooter getReportFooter() {
        return new XMLReportFooter();
    }
}
