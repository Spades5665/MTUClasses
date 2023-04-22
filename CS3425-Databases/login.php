<html>
    <body>
        <?php
            require "db.php";
            session_start();
            if (isset($_POST["logoutButton"])) {
                session_destroy();
            }
            if ( isset($_POST["loginButton"]) ) {
                if (authenticate($_POST["username"], $_POST["password"], $_POST["profession"]) == 1) {
                    if ($_POST["profession"] == "student") {
                        $_SESSION["username"] = $_POST["username"];
                        header("LOCATION:student-main.php");
                        return;
                    } else if ($_POST["profession"] == "instructor") {
                        $_SESSION["username"] = $_POST["username"];
                        header("LOCATION:instructor-main.php");
                        return;
                    }
                } else {
                    echo '<p style="color:red">Incorrect username and password</p>';
                }
            }
        ?>
        <form method = post action = login.php>
            Username: <input type = "text" name = "username"><br>
            Password: <input type = "password" name = "password"><br>
            Student: <input type = "radio" name = "profession" value = "student">
            Instructor: <input type = "radio" name = "profession" value = "instructor"><br>
            <button type = "submit" name = "loginButton">Login</button>
        </form>    
        
    </body>
</html>
