<html>
    <body>
        <style>
            table, th, td {
                border: 1px solid black;
                border-collapse: collapse;
            }
        </style>

        <?php
            session_start();
            if (!isset($_SESSION['username'])) {
                header("LOCATION:login.php");
            }
            require "db.php";            
            if (isset($_POST["accountButton"])) {
                $accounts = get_accounts($_SESSION["username"]);
        ?>
            <table>
                <tr>
                <th>Account</th>
                <th>Balance</th>
            </tr>
        <?php
                foreach ($accounts as $row) {
                    echo "<tr>";
                    echo "<td>" . $row[0] . "</td>";
                    echo "<td>" . $row[1] . "</td>";
                    echo "</tr>";
                }
            }

            if (isset($_POST["transferButton"])) {
        ?>
            <form method = post action = bankoperation.php>
                From account: <input type = "text" id = "from_account" name = "from_account"><br>
                To account: <input type = "text" id = "to_account" name = "to_account"><br>
                Amount: <input type = "text" id = "amount" name = "amount"><br>
                <button type = "submit" name = "confirmButton">Confirm</button>
            </form>
        <?php    
            }

            if (isset($_POST["confirmButton"])) {
                $from = $_POST["from_account"];
                $to = $_POST["to_account"];
                $amount = $_POST["amount"];
                $user = $_SESSION["username"];
                transfer($from, $to, $amount, $user);
            }
        ?>

        
        
    </body>
</html>