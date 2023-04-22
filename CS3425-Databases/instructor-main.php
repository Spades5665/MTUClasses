<html>
    <body>
        <?php
            session_start();
            require "db.php";   
            // TODO: uncomment
            // if (!isset($_SESSION["username"])) {
            //     header("LOCATION:login.php");
            // } else {
            //     echo '<p align="right"> Dear instructor, '. $_SESSION["username"].', Welcome</p>';
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
        <p>Here are the courses you are teaching: </p>

        <table>
            <tr>
            <th>CID</th>
            <th>Title</th>
            <th>Credit</th>
            </tr>
        
        <?php
            $courses = get_courses("Alice"); // Just replace "Alice" with $_SESSION["username"]
            foreach ($courses as $row) {
                echo "<tr>";
                echo "<td>" . $row[0] . "</td>";
                echo "<td>" . $row[1] . "</td>";
                echo "<td>" . $row[2] . "</td>";
                echo "</tr>";
            }
        ?>

        </table>

        <p>Please enter the Course ID first, then press one of the buttons.</p>

        <form method = post action = instructoroperation.php>
            <button type = "submit" name = "reviewButton">Review Survey Questions</button>
            <button type = "submit" name = "checkButton">Check Survey Result</button>
            <button type = "submit" name = "createButton">Create Instructor Questions</button>
        </form>
        
    </body>
</html>