package eu.jpereira.trainings.designpatterns.creational.builder;

import java.util.HashMap;

import eu.jpereira.trainings.designpatterns.creational.builder.ReportBodyBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.html.HTMLReportBodyBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.json.JSONReportBodyBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.xml.XMLReportBodyBuilder;

public class ReportType {
    private ReportType() throws InstantiationError {
        throw new InstantiationError("This is a static class!");
    }

    private static HashMap<String, ReportBodyBuilder> types = new HashMap<String, ReportBodyBuilder>();
    static {
        types.put("XML", new XMLReportBodyBuilder());
        types.put("HTML", new HTMLReportBodyBuilder());
        types.put("JSON", new JSONReportBodyBuilder());
    }

    public static HashMap<String, ReportBodyBuilder> getTypes() {
        return types;
    }
}
