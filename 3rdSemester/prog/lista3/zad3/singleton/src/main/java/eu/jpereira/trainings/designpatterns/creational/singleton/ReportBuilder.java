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
package eu.jpereira.trainings.designpatterns.creational.singleton;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import eu.jpereira.trainings.designpatterns.creational.singleton.crwaling.CannotCrawlException;
import eu.jpereira.trainings.designpatterns.creational.singleton.crwaling.DummySiteCrawler;
import eu.jpereira.trainings.designpatterns.creational.singleton.crwaling.SiteCrawler;

/**
 * Singleton ReportBuilder using double-checked locking for thread safety. 
 */
public class ReportBuilder {

	// Instance variables
	private Map<String, StringBuffer> sitesContens;

	private SiteCrawler siteCrawler;

	// Class variables
	// Single instance
	private static volatile ReportBuilder instance;
	private static final List<String> configuredSites = new ArrayList<>();	
	
	static {
		configuredSites.add("http://www.wikipedia.com");
		configuredSites.add("http://stackoverflow.com");
	}

	//  private constructor to prevent instantiation
	private ReportBuilder() {
		initialize();
	}

	/**
	 * Very time consuming initialize method...
	 */
	private void initialize() {

		//defer it to an factory method
		this.siteCrawler = createSiteCrawler();
		
		// Now crawl some pre-defined sites
		for (String url : configuredSites) {
			this.siteCrawler.withURL(url);
		}
		try {
			this.setSitesContens(this.siteCrawler.crawl().packSiteContens());
		} catch (CannotCrawlException e) {
			throw new RuntimeException("Could not load sites: " + e.getMessage());
		}

	}

	/**
	 * Factory method with default implementation
	 * 
	 * @return
	 */
	protected SiteCrawler createSiteCrawler() {
		return new DummySiteCrawler();
	}

	/**
	 * Get a single instance of type ReportBuilder using double-checked lock.
	 * 
	 * @return instance of the singleton
	 */
	public static ReportBuilder getInstance() {
		if (instance == null) {
			synchronized (ReportBuilder.class) {
				if (instance == null) {
					instance = new ReportBuilder();
				}
			}
		}
		return instance;
	}

	/**
	 * 
	 * @return the sitesContens
	 * 
	 */
	public Map<String, StringBuffer> getSitesContens() {
		return sitesContens;
	}

	/**
	 * @param sitesContens
	 *            the sitesContens to set
	 */
	private void setSitesContens(Map<String, StringBuffer> sitesContens) {
		this.sitesContens = sitesContens;
	}

	/**
	 * Reset the singleton
	 */
	public static void resetInstance() {
		// added lock
		synchronized (ReportBuilder.class) {
			instance = null;
		}
	}
}
