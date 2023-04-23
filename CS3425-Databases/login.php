<html>
    <body>
        <?php
            require "db.php";
            session_start();
            if ( isset($_POST["loginButton"]) ) {
                if (authenticate($_POST["username"], $_POST["password"], $_POST["profession"]) == 1) {
                    $_SESSION["username"] = $_POST["username"];
                    $_SESSION["profession"] = $_POST["profession"];
                    $dbh = connectDB();
                    if ($_POST["profession"] == "student") {
                        $statement = $dbh->prepare("SELECT count(*) FROM student where sName = :username and sLogin = 0 ");
                    } else if ($_POST["profession"] == "instructor") {
                        $statement = $dbh->prepare("SELECT count(*) FROM instructor where iName = :username and iLogin = 0 ");
                    }
                    $statement->bindParam(":username", $_POST["username"]);
                    $result = $statement->execute();
                    $row=$statement->fetch();
                    $dbh=null;

                    if ($row[0] == 1) {
                        header("LOCATION:reset-password.php");
                        return;
                    }

                    header("LOCATION:main.php");
                    return;
                } else {
                    echo '<p style="color:red">Incorrect username and password</p>';
                }
            }
        ?>
        <form method = post action = login.php>
            Username: <input type = "text" name = "username"><br>
            Password: <input type = "password" name = "password"><br>
            Student: <input type = "radio" name = "profession" value = "student" required>
            Instructor: <input type = "radio" name = "profession" value = "instructor" required><br>
            <button type = "submit" name = "loginButton">Login</button>
        </form>    
        
    </body>
</html>
