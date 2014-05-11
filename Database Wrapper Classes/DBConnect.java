/**
 * puneeth
 * 3:34:10 AM
 * May 11, 2014
 */
package com.akshaya.db;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream.GetField;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.hp.hpl.jena.util.FileUtils;

/**
 * @author puneeth
 *
 */
public class DBConnect {

	Connection conn = null;
	String dbUrl = "jdbc:mysql://localhost:3306/";
	String dbName = "akshaya_patra";
	String driver = "com.mysql.jdbc.Driver";
	String userName = "root";
	String password = "12345";
	/**
	 * @return the conn
	 */
	public Connection getConn() {
		return conn;
	}
	/**
	 * @param conn the conn to set
	 */
	public void setConn(Connection conn) {
		this.conn = conn;
	}
	/**
	 * @return the dbUrl
	 */
	public String getDbUrl() {
		return dbUrl;
	}
	/**
	 * @param dbUrl the dbUrl to set
	 */
	public void setDbUrl(String dbUrl) {
		this.dbUrl = dbUrl;
	}
	/**
	 * @return the dbName
	 */
	public String getDbName() {
		return dbName;
	}
	/**
	 * @param dbName the dbName to set
	 */
	public void setDbName(String dbName) {
		this.dbName = dbName;
	}
	/**
	 * @return the driver
	 */
	public String getDriver() {
		return driver;
	}
	/**
	 * @param driver the driver to set
	 */
	public void setDriver(String driver) {
		this.driver = driver;
	}
	/**
	 * @return the userName
	 */
	public String getUserName() {
		return userName;
	}
	/**
	 * @param userName the userName to set
	 */
	public void setUserName(String userName) {
		this.userName = userName;
	}
	/**
	 * @return the password
	 */
	public String getPassword() {
		return password;
	}
	/**
	 * @param password the password to set
	 */
	public void setPassword(String password) {
		this.password = password;
	}

	// Constructor: connects to database and loads the seed's (URL's) from the
	// database.
	public DBConnect() throws SQLException {
		connectDatabase();
		// loadData(conn);
	}

	// Connects to the database
	private void connectDatabase() {

		try {
			Class.forName(getDriver()).newInstance();
			conn = DriverManager.getConnection(getDbUrl() + getDbName(),
					getUserName(), getPassword());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// Closing the database.
	public void closeDatabase(Connection conn) throws SQLException {
		conn.close();
	}

	
	//Get the Number of Kitchens per City
	public ArrayList<Location> getKitchen(String city) throws SQLException, IOException{

		Statement stmt = null;
		ResultSet rs = null;

		ArrayList<Location> returns = new ArrayList<>();

		stmt = conn.createStatement();
		System.out.println("Started loading the data from database!");

		if (stmt.execute("SELECT * FROM kitchen")) {
			rs = stmt.getResultSet();
		} else {
			System.err.println("select failed");
		}
		while (rs.next()) {
			System.out.println(rs.getInt(1));
			System.out.println(rs.getDouble(3));
			System.out.println(rs.getDouble(4));

			Location loc = new Location();
			loc.setId(rs.getInt(1));
			loc.setLatitude(rs.getDouble(3));
			loc.setLongitude(rs.getDouble(4));

			returns.add(loc);
		}
		return returns;

	}

	//Get the Number of Schoold for a given city
	public ArrayList<Location> getSchools(String city) throws SQLException, IOException{

		Statement stmt = null;
		Statement stmt2 = null;
		ResultSet rs = null;
		ResultSet rs2 = null;

		ArrayList<Location> returns = new ArrayList<>();

		stmt = conn.createStatement();
		stmt2 = conn.createStatement();
		System.out.println("Started loading the data from database!");

		if (stmt.execute("SELECT * FROM time_distance")) {
			rs = stmt.getResultSet();
		} else {
			System.err.println("select failed");
		}
		while (rs.next()) {
			/*System.out.println(rs.getInt(1));
			System.out.println(rs.getDouble(3));
			System.out.println(rs.getDouble(4));*/

			if (stmt2.execute("SELECT * FROM schools where Slno="+rs.getInt(1))) {
				rs2 = stmt2.getResultSet();
			} else {
				System.err.println("select failed");
			}
			while (rs2.next()) {
				/*System.out.println(rs.getInt(1));
				System.out.println(rs.getDouble(3));
				System.out.println(rs.getDouble(4));*/

				try {

					Location loc = new Location();
					loc.setId(rs2.getInt(1));

					loc.setLatitude(rs2.getDouble(5));
					loc.setLongitude(rs2.getDouble(4));

					returns.add(loc);

				} catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
				}

			}

		}
		return returns;

	}

	
	//Get the Different Routes currently in operation in the city
	public ArrayList<String> getDistinctRoutes(String city) throws SQLException, IOException{

		Statement stmt = null;
		ResultSet rs = null;

		ArrayList<String> Route_Codes = new ArrayList<>();

		stmt = conn.createStatement();
		System.out.println("Started loading the data from database!");

		if (stmt.execute("SELECT DISTINCT Route_Code FROM schools")) {
			rs = stmt.getResultSet();
		} else {
			System.err.println("select failed");
		}
		while (rs.next()) {

				Route_Codes.add(rs.getString(1));				
			}
		
		return Route_Codes;
		}
		
	
	//Get the Different schools that are served by a given route
	public ArrayList<Integer> getSchoolsinRoute(String Route) throws SQLException, IOException{

		Statement stmt = null;
		ResultSet rs = null;

		ArrayList<Integer> SchoolsInRoute = new ArrayList<>();

		stmt = conn.createStatement();
		System.out.println("Started loading the data from database!");

		if (stmt.execute("SELECT * FROM schools where Route_Code like \'"+Route+"\'")) {
			rs = stmt.getResultSet();
		} else {
			System.err.println("select failed");
		}
		while (rs.next()) {

			SchoolsInRoute.add(rs.getInt(1));				
			}
		
		return SchoolsInRoute;
		}
	
	
	//Tells the Number Of Valid Schools, i.e. The schools which have the valid latitude and longitude. 
	public ArrayList<Integer> getValidSchoolsinRoute(ArrayList<Integer> SchoolsInRoute) throws SQLException, IOException{

		Statement stmt = null;
		ResultSet rs = null;

		ArrayList<Integer> ValidSchools = new ArrayList<>();

		stmt = conn.createStatement();
		System.out.println("Started loading the data from database!");

		for (int i = 0; i < SchoolsInRoute.size(); i++) {
			if (stmt.execute("SELECT * FROM time_distance where School="+SchoolsInRoute.get(i))) {
				rs = stmt.getResultSet();
			} else {
				System.err.println("select failed");
			}
			
			if (!rs.next()){
				//ResultSet is empty
				System.out.println("No OP");
			}
			
			while (rs.next()) {
				ValidSchools.add(SchoolsInRoute.get(0));				
				}
			
		}
		
			return ValidSchools;
		}


//Main Program to the Database Wrapper
	public static void main(String[] args) throws SQLException, IOException{
		DBConnect db = new DBConnect();
		//ArrayList<Location> kitchens  = db.getKitchen("Bangalore");

		//System.out.println(kitchens.get(0).getLatitude());

		//System.out.println(Outty.get(2));


		//ArrayList<Location> schools  = db.getSchools("Bangalore");

		//System.out.println(schools.get(0).getLatitude());
		//System.out.println("Size of Schools coordinates: "+schools.size());

		ArrayList<String> routes = db.getDistinctRoutes("city");
		System.out.println(">>>"+routes.size()+"Last Element"+routes.get(routes.size()-1));
				
		
		for (int j = 0; j < routes.size(); j++) {
			ArrayList<Integer> r_s = db.getSchoolsinRoute(routes.get(j));
			ArrayList<Integer> validated  = db.getValidSchoolsinRoute(r_s);
			
			PrintWriter pw = new PrintWriter(new FileOutputStream("Routes"+j+".txt"));
		    for (Integer integer : validated) {
		    	pw.println(routes.get(j));
		    	pw.println(integer);
			    pw.close();
			}
		        
		}
		
		//System.out.println(r_s.size());
		
		//System.out.println(validated.size());
	}
	

}
