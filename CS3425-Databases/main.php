<html>
    <body>
        <?php
            require "db.php"; 
            session_start();  
            // TODO: uncomment
            if (!isset($_SESSION["username"])) {
                header("LOCATION:login.php");
            } else {
                if ($_SESSION["profession"] == "instructor") {
                    echo '<p align="right"> Dear Instructor '. $_SESSION["username"].', Welcome</p>';
                } else {
                    echo '<p align="right"> Dear Student '. $_SESSION["username"].', Welcome</p>';
                }
                
        ?>
        <form method = post>
            <p align = "right">
                <button type = "submit" name = "logoutButton">Logout</button>
            </p>
        </form>
        <?php
            }
            if (isset($_POST["logoutButton"])) {
                session_destroy();
                header("LOCATION:login.php");
                exit();
            }

            if ($_SESSION["profession"] == "instructor") {
        ?>

        <p>Here are the courses you are teaching: </p>

        <table>
            <tr>
            <th>CID</th>
            <th>Title</th>
            <th>Credit</th>
            </tr>
        
        <?php
                if (isset($_POST["reviewButton"]) ) {

                    $dbh = connectDB();
                    $statement = $dbh->prepare("select count(*) from (select course.cID from course natural join instructor where instructor.iName = :name) as t where t.cID = :cid");
                    $statement->bindParam(":name", $_SESSION["username"]);
                    $statement->bindParam(":cid", $_POST["instructorCourseID"]);
                    $result = $statement->execute();
                    $row = $statement->fetch();           
                    $dbh = null;
                    if ($row[0] == 1) {
                        $_SESSION["CID"] = $_POST["instructorCourseID"];
                        $_SESSION["PID"] = 1;
                        header("LOCATION:instructor.php");
                        return;
                    } else {
                        echo '<p style="color:red">Please choose a class you teach</p>';
                    }                    
                    
                } else if (isset($_POST["checkButton"]) ) {
                    
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select count(*) from (select course.cID from course natural join instructor where instructor.iName = :name) as t where t.cID = :cid");
                    $statement->bindParam(":name", $_SESSION["username"]);
                    $statement->bindParam(":cid", $_POST["instructorCourseID"]);
                    $result = $statement->execute();
                    $row = $statement->fetch();           
                    $dbh = null;
                    if ($row[0] == 1) {
                        $_SESSION["CID"] = $_POST["instructorCourseID"];
                        $_SESSION["PID"] = 2;
                        header("LOCATION:instructor.php");
                        return;
                    } else {
                        echo '<p style="color:red">Please choose a class you teach</p>';
                    }      

                } else if (isset($_POST["createButton"]) ) {
                    
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select count(*) from (select course.cID from course natural join instructor where instructor.iName = :name) as t where t.cID = :cid");
                    $statement->bindParam(":name", $_SESSION["username"]);
                    $statement->bindParam(":cid", $_POST["instructorCourseID"]);
                    $result = $statement->execute();
                    $row = $statement->fetch();           
                    $dbh = null;
                    if ($row[0] == 1) {
                        $_SESSION["CID"] = $_POST["instructorCourseID"];
                        $_SESSION["PID"] = 3;
                        header("LOCATION:instructor.php");
                        return;
                    } else {
                        echo '<p style="color:red">Please choose a class you teach</p>';
                    }      

                }
                
                $courses = i_get_courses($_SESSION["username"]);
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

        <form method = post>
            Course: <input type = "text" name = "instructorCourseID"><br>
            <button type = "submit" name = "reviewButton">Review Survey Questions</button>
            <button type = "submit" name = "checkButton">Check Survey Result</button>
            <button type = "submit" name = "createButton">Create Instructor Questions</button>
        </form>

        <?php
            } else {
        ?>

        <p>Here are the courses you are taking: </p>

        <table>
            <tr>
            <th>CID</th>
            <th>Title</th>
            <th>Credit</th>
            <th>Teacher</th>
            <th>surveyTime</th>
            </tr>

        <?php
                if (isset($_POST["registerButton"]) ) { 
                    
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select count(*) from (select course.cID from course natural join takes natural join student where student.sName = :name) as t where t.cID = :cid");
                    $statement->bindParam(":name", $_SESSION["username"]);
                    $statement->bindParam(":cid", $_POST["studentCourseID"]);
                    $result = $statement->execute();
                    $row = $statement->fetch();           
                    $dbh = null;
                    if ($row[0] == 0) {
                        $_SESSION["CID"] = $_POST["studentCourseID"];
                        $_SESSION["SID"] = 1;
                        header("LOCATION:student.php");
                        return;
                    } else {
                        echo '<p style="color:red">Please choose a class you are not already enrolled in</p>';
                    }
                    
                } else if (isset($_POST["takeButton"]) ) { 
                    
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select count(*) from (select course.cID, takes.sCompleted from course natural join takes natural join student where student.sName = :name) as t where t.cID = :cid and sCompleted is null");
                    $statement->bindParam(":name", $_SESSION["username"]);
                    $statement->bindParam(":cid", $_POST["studentCourseID"]);
                    $result = $statement->execute();
                    $row = $statement->fetch();           
                    $dbh = null;
                    if ($row[0] == 1) {
                        $_SESSION["CID"] = $_POST["studentCourseID"];
                        $_SESSION["SID"] = 2;
                        header("LOCATION:student.php");
                        return;
                    } else {
                        echo '<p style="color:red">Please choose a class you are enrolled in and have not taken the survey for</p>';
                    }
                    
                } 
                
                $courses = s_get_courses($_SESSION["username"]);
                foreach ($courses as $row) {
                    echo "<tr>";
                    echo "<td>" . $row[0] . "</td>";
                    echo "<td>" . $row[1] . "</td>";
                    echo "<td>" . $row[2] . "</td>";
                    echo "<td>" . $row[3] . "</td>";
                    echo "<td>" . $row[4] . "</td>";
                    echo "</tr>";
                }
        ?>

        </table>

        <p>Here is the list of classes that you are not enrolled in yet: </p>

        <table>
            <tr>
            <th>CID</th>
            <th>Title</th>
            <th>Credit</th>
            <th>Teacher</th>
            <th>Department</th>
            </tr>

        <?php
            $courses = s_get_not_courses($_SESSION["username"]);
            foreach ($courses as $row) {
                echo "<tr>";
                echo "<td>" . $row[0] . "</td>";
                echo "<td>" . $row[1] . "</td>";
                echo "<td>" . $row[2] . "</td>";
                echo "<td>" . $row[3] . "</td>";
                echo "<td>" . $row[4] . "</td>";
                echo "</tr>";
            }
        ?>

        </table>

        <p>To register for a new class, type in the CID then click on the register button<br>To take a survey, type in the CID then click on the take survey button</p>

        <form method = post>
            Course: <input type = "text" name = "studentCourseID"><br>
            <button type = "submit" name = "registerButton">Register New Course</button>
            <button type = "submit" name = "takeButton">Take Survey</button>
        </form>

        <?php        
            }
        ?>
        
    </body>
</html>