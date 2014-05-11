/**
 * puneeth
 * 4:12:55 AM
 * May 11, 2014
 */
package com.akshaya.db;

/**
 * @author puneeth
 * Class representing the data points. 
 */


public class Location {

	private int id;
	private Double latitude;
	private Double longitude;
	
	/**
	 * @return the id
	 */
	public int getId() {
		return id;
	}

	/**
	 * @param id the id to set
	 */
	public void setId(int id) {
		this.id = id;
	}

	/**
	 * @return the latitude
	 */
	public Double getLatitude() {
		return latitude;
	}

	/**
	 * @param latitude the latitude to set
	 */
	public void setLatitude(Double latitude) {
		this.latitude = latitude;
	}

	/**
	 * @return the longitude
	 */
	public Double getLongitude() {
		return longitude;
	}

	/**
	 * @param longitude the longitude to set
	 */
	public void setLongitude(Double longitude) {
		this.longitude = longitude;
	}

	public Location(){
		this.id = id;
		this.latitude = latitude;
		this.longitude = longitude;
		
	}
}
