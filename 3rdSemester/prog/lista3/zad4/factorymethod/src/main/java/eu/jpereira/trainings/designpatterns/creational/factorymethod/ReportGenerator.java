/**
 * Copyright 2011 Joao Miguel Pereira
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
package eu.jpereira.trainings.designpatterns.creational.factorymethod;

import java.util.HashMap;

import eu.jpereira.trainings.designpatterns.creational.factorymethod.HTMLReportFactory;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.JSONReportFactory;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.PDFReportFactory;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.ReportFactory;
import eu.jpereira.trainings.designpatterns.creational.factorymethod.XMLReportFactory;

/**
 * The Report Generator will create reports based on a given type
 * @author jpereira
 *
 */
public class ReportGenerator {
	private final HashMap<String, ReportFactory> reportFactoryMap;


	public ReportGenerator() {
		reportFactoryMap = new HashMap<>();
		reportFactoryMap.put("JSON", new JSONReportFactory());
		reportFactoryMap.put("XML", new XMLReportFactory());
		reportFactoryMap.put("HTML", new HTMLReportFactory());
		reportFactoryMap.put("PDF", new PDFReportFactory());
	}

	/**
	 * Generate a new report.
	 * @param data The report data
	 * @param type the type of report
	 * @return the generated report, or null of type is unknown
	 */
	public Report generateReport(ReportData data, String type) {
		ReportFactory factory = reportFactoryMap.get(type);
		if (factory == null) {
			return null;
		}

		Report generatedReport = factory.createReport();
		generatedReport.generateReport(data);
		return generatedReport;
	}
}
