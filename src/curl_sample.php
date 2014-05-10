#!/usr/bin/php
<?php
/*$DB_Server = "localhost"; //your MySQL Server
$DB_Username = "root"; //your MySQL User Name
$DB_Password = "bitnami"; //your MySQL Password
$DB_DBName = "erp"; //your MySQL Database Name

$Connect = @mysql_connect($DB_Server, $DB_Username, $DB_Password)
        or die("Couldn't connect to MySQL:<br>" . mysql_error() . "<br>" . mysql_errno());

$Db = @mysql_select_db($DB_DBName, $Connect)
        or die("Couldn't select database:<br>" . mysql_error() . "<br>" . mysql_errno());*/
$api_key = 'AIzaSyD9i6uXAIyEQuEaOsHxiHRFuKEC0C5Yd44';
$auth_key='';
$headr = array();
$headr[] = 'api_key:'.$api_key;
#$headr[] = 'auth_key:'.$auth_key;

/*function curlGet($url,$headr)
{
    $crl = curl_init();
    curl_setopt($crl, CURLOPT_URL, $url);
    curl_setopt($crl, CURLOPT_HTTPHEADER,$headr);
    curl_setopt($crl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($crl, CURLOPT_HTTPGET,true);
    $reply = curl_exec($crl);

    if ($reply === false) {
       print_r('Curl error: ' . curl_error($crl));
    }
    return $reply;
}*/
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

function curlPost($url,$headr,$fields_string)
{
    $crl=curl_init();
    curl_setopt($crl,CURLOPT_URL, $url);
    curl_setopt($crl,CURLOPT_RETURNTRANSFER,true);
    curl_setopt($crl, CURLOPT_HTTPHEADER,$headr);
    curl_setopt($crl,CURLOPT_POSTFIELDS, $fields_string);
     $reply = curl_exec($crl);
    if ($reply === false) {
       print_r('Curl error: ' . curl_error($crl));
    }
    return $reply;
}

$url='https://maps.googleapis.com/maps/api/distancematrix/json?origins=12.885525,77.556328&destinations=13.010077,77.551135&sensor=false&key=AIzaSyD9i6uXAIyEQuEaOsHxiHRFuKEC0C5Yd44';
$reply=curlGet($url);
echo $reply;