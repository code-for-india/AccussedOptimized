#!/usr/bin/php
<?php
$DB_Server = "localhost"; //your MySQL Server
$DB_Username = "root"; //your MySQL User Name
$DB_Password = "justeat"; //your MySQL Password
$DB_DBName = "akshaya_patra"; //your MySQL Database Name

$Connect = @mysql_connect($DB_Server, $DB_Username, $DB_Password)
        or die("Couldn't connect to MySQL:<br>" . mysql_error() . "<br>" . mysql_errno());
$Db = @mysql_select_db($DB_DBName, $Connect)
        or die("Couldn't select database:<br>" . mysql_error() . "<br>" . mysql_errno());

#$input_file = $argv[1];


#array str_getcsv ( string $input [, string $delimiter = "," [, string $enclosure = '"' [,string $escape = "\\" ]]] )


if (empty($argv[1])) die("The json file name or URL is missed\n");
$file_name = $argv[1];
$file = fopen($file_name,"r");
$counter=0;
while(! feof($file))
  {
  	$data=fgetcsv($file);
  	#print_r(fgetcsv($file));
  	$num = count($data);
    $counter++;
  
  		$SchoolName=$data[0];
  		$SchoolName=mysql_real_escape_string($SchoolName);
  		$Kitchen_Location=$data[1];
  		$Latitude=$data[2];
  		$Longitude=$data[3];
  	   $Route_Code=$data[6];
  	
  			
  	
  			$Route_Name=$data[7];

  		$sql="INSERT INTO schools(SchoolName,Kitchen_Location,Latitude,Longitude,Route_Code,Route_Name) VALUES('$SchoolName','$Kitchen_Location','$Latitude','$Longitude','$Route_Code','$Route_Name')";
		$result1 = mysql_query($sql) or die("Couldn't execute query:<br>" . mysql_error() . "<br>" . mysql_errno());

  	}

  	
  echo $counter;

fclose($file);

?>