package eu.jpereira.trainings.designpatterns.creational.abstractfactory;

import java.util.HashMap;

import eu.jpereira.trainings.designpatterns.creational.abstractfactory.ReportFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.json.JSONReportFactory;
import eu.jpereira.trainings.designpatterns.creational.abstractfactory.xml.XMLReportFactory;

public class ReportType {
    private ReportType() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static HashMap<String, ReportFactory> factoryMap = new HashMap<String, ReportFactory>();
    static {
        factoryMap.put("JSON", new JSONReportFactory());
        factoryMap.put("XML", new XMLReportFactory());
    }

    public static HashMap<String, ReportFactory> getFactoryMap() {
        return factoryMap;
    }
}
