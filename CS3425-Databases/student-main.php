<html>
    <body>
        <?php
            session_start();
            // TODO: uncomment
            // if (!isset($_SESSION["username"])) {
            //     header("LOCATION:login.php");
            // } else {
            //     echo '<p align="right"> Dear student, '. $_SESSION["username"].', Welcome</p>';
            ?>
        <form method = post>
            <p align = "right">
                <button type = "submit" name = "logoutButton">Logout</button>
            </p>
        </form>
        <?php
            // }
            if (isset($_POST["logoutButton"])) {
                session_destroy();
                header("LOCATION:login.php");
                exit();
            }
        ?>
        <p>Welcome to out online minibank!</p>
        <p>We can help you to transfer the money or display your accounts.</p>
        <p>What would you like to do? Please click one of the buttons.</p>

        <form method = post action = bankoperation.php>
            <button type = "submit" name = "transferButton">Transfer</button>
            <button type = "submit" name = "accountButton">Accounts</button>
        </form>
        
    </body>
</html>