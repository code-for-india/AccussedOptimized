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

function curlGet($url)
{
    $crl = curl_init();
    curl_setopt($crl, CURLOPT_URL, $url);
    //curl_setopt($crl, CURLOPT_HTTPHEADER,$headr);
    curl_setopt($crl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($crl, CURLOPT_HTTPGET,true);
    $reply = curl_exec($crl);

    if ($reply === false) {
       print_r('Curl error: ' . curl_error($crl));
    }
    return $reply;
}



if (empty($argv[1])) die("The json file name or URL is missed\n");
$file_name = $argv[1];
$file = fopen($file_name,"r");
$counter=0;
while(! feof($file))
  {
  	$data=fgetcsv($file);
  	#print_r(fgetcsv($file));
  	$num = count($data);
    
  
  		$SchoolName=$data[0];
  		$SchoolName=mysql_real_escape_string($SchoolName);
  		$Kitchen_Location=$data[1];

  	 	$Latitude=$data[2];
  		$Longitude=$data[3];
  	  $Route_Code=$data[6];
  	
  			
  	
  			$Route_Name=$data[7];
        $counter++;

    $sql="SELECT Longitude,Latitude from schools where SlNo=".$counter;
    $result1 = mysql_query($sql) or die("Couldn't execute query:<br>" . mysql_error() . "<br>" . mysql_errno());
    $row = mysql_fetch_row($result1);
    $Longitude=$row[0];
    $Latitude=$row[1];
   // echo $Latitude;
    //echo $Longitude;
    //die();


  		/*$sql="INSERT INTO schools(SchoolName,Kitchen_Location,Latitude,Longitude,Route_Code,Route_Name) VALUES('$SchoolName','$Kitchen_Location','$Latitude','$Longitude','$Route_Code','$Route_Name')";
		$result1 = mysql_query($sql) or die("Couldn't execute query:<br>" . mysql_error() . "<br>" . mysql_errno());*/
    echo $Kitchen_Location;
    if($Kitchen_Location=='hkh')
      {

        $lat='13.010077';
        $long='77.551135';
    }
  else if($Kitchen_Location=='vkh')
      {

        $lat='12.885525';
        $long='77.556328';
    }
    if(($Latitude!=NULL)&&($Longitude!=NULL))
    {
      echo $lat;
      echo $long;
      $url='https://maps.googleapis.com/maps/api/distancematrix/json?origins='.$lat.','.$long.'&destinations='.$Latitude.','.$Longitude.'&sensor=false&key=AIzaSyD9i6uXAIyEQuEaOsHxiHRFuKEC0C5Yd44';
      $reply=curlGet($url);
      echo $reply;
      
      $reply= json_decode($reply,true);
      $distance=$reply['rows'][0]['elements'][0]['distance']['value'];
      $duration=$reply['rows'][0]['elements'][0]['duration']['value'];
    if(isset($distance)&&isset($duration)){      
      $sql="INSERT INTO time_distance(Kitchen,School,Time,Distance) VALUES('$Kitchen_Location',$counter,$duration,$distance)";
    $result1 = mysql_query($sql) or die("Couldn't execute query:<br>" . mysql_error() . "<br>" . mysql_errno());
}







    }


  	}

  	
  

fclose($file);

?>