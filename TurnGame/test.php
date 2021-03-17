<?php
// 建立MySQL伺服器連接和開啟資料庫 
$json = file_get_contents('php://input');
if(!empty($json)) {
   $data = json_decode($json, true);
   $dsn = "mysql:dbname=ue4db;host=localhost;port=3306";
   $username = "root";
   $password = "123456";
   $link = new PDO($dsn, $username, $password);
   // 指定PDO錯誤模式和錯誤處理
   //$link->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
   $sql = "insert into item (Item_Name, Item_Rarity) values (:Item_Name, 0)";
   $stmt = $link -> prepare($sql);
   $stmt ->bindParam(':Item_Name', $data["Item_Name"],PDO::PARAM_STR);
   $stmt ->execute();
   echo "123456";
}
?>
