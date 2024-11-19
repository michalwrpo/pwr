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
package eu.jpereira.trainings.designpatterns.creational.builder;

import java.util.Iterator;

import eu.jpereira.trainings.designpatterns.creational.builder.model.Report;
import eu.jpereira.trainings.designpatterns.creational.builder.model.SaleEntry;
import eu.jpereira.trainings.designpatterns.creational.builder.json.JSONReportBodyBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.xml.XMLReportBodyBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.ReportBodyBuilder;
import eu.jpereira.trainings.designpatterns.creational.builder.html.HTMLReportBodyBuilder;

public class ReportAssembler {

	private SaleEntry saleEntry;

	/**
	 * @param reportDate
	 */
	public void setSaleEntry(SaleEntry saleEntry) {
		this.saleEntry = saleEntry;
	}

	// changed basically the whole function
    /**
     * @param type
     * @return
     */
    public Report getReport(String type) {
        ReportBodyBuilder builder;

        switch (type.toUpperCase()) {
            case "JSON":
                builder = new JSONReportBodyBuilder();
                break;
            case "XML":
                builder = new XMLReportBodyBuilder();
                break;
            case "HTML":
                builder = new HTMLReportBodyBuilder();
                break;
            default:
                throw new IllegalArgumentException("Unsupported report type: " + type);
        }

        builder.setSaleEntry(this.saleEntry);
        return builder.buildReport();
    }
}
