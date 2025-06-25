<html>
    <body>
        <?php
            require "db.php";
            session_start();
            if (isset($_POST["updatePassButton"])) {
                $dbh = connectDB();
                if ($_SESSION["profession"] == "instructor") {
                    $statement = $dbh->prepare("update instructor set iPassword = sha2(:newPass,256), iLogin = 1 where iName = :username");
                } else {
                    $statement = $dbh->prepare("update student set sPassword = sha2(:newPass,256), sLogin = 1 where sName = :username");
                }
                $statement->bindParam(":username", $_SESSION["username"]);
                $statement->bindParam(":newPass", $_POST["newPassword"]);
                $result = $statement->execute();
                $dbh = null;

                header("LOCATION:main.php");
                return;
            }
        ?>
        <form method = post action = reset-password.php>
            New Password: <input type = "password" name = "newPassword"><br>
            <button type = "submit" name = "updatePassButton">Update Password</button>
        </form>    
        
    </body>
</html>