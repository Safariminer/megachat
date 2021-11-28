<?php


if($_GET['try'] == "send"){
$oldlog = file_get_contents("log.txt");
$log = fopen("log.txt", "w") or die("Unable to open file!");

fwrite($log, $oldlog);
fwrite($log, "\n");
fwrite($log, base64_decode($_GET['msg']));

fclose($log);
echo base64_decode($_GET['msg']);
}
if($_GET['try'] == "get"){
  echo file_get_contents("log.txt");
}


?>
