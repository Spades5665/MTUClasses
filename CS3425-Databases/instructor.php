<html>
    <body>
        
        <?php
            require "db.php";
            session_start();
            if ($_SESSION["PID"] == 1) {
                if (isset($_POST["backButton"])) {
                    header("LOCATION:main.php");
                    return;
                }

                echo "<h1>Survey Questions for ". $_SESSION["CID"] ."<br> </h1>";

                $dbh = connectDB();
                $statement = $dbh->prepare("select t1.section, t1.qID, t1.description as qDescription, choices.chID, choices.description as cDescription from (select section, qID, description from questions where section = :univ or department = :dept or cID = :CID) as t1 join choices on t1.qID = choices.qID");
                $statement->bindValue(":univ", "university");
                $statement->bindValue(":dept", substr($_SESSION["CID"], 0, strlen($_SESSION["CID"]) - 4));
                $statement->bindParam(":CID", $_SESSION["CID"]);
                $result = $statement->execute();
                $rows = $statement->fetchAll();
                $dbh = null;

                $survey = array();
                
                foreach ($rows as $row) {
                    $qID = $row["qID"];

                    if (!isset($survey[$qID])) {
                        $survey[$qID] = array();
                        $survey[$qID][] = $row["section"];
                        $survey[$qID][] = $row["qDescription"];
                    }
                    
                    $survey[$qID][] = $row["cDescription"];
                }

                $firstHeader = 0;
                $question = 0;
                echo "<form method = 'post' action = 'instructor.php'>";
                foreach ($survey as $qID => $choices) {
                    $first = 0;
                    foreach ($choices as $choice) {
                        if ($first == 0) {
                            $first++;
                            if ($firstHeader == 0 && $choice == "university") {
                                $firstHeader++;
                                echo "<h2> University Questions<br> </h2>";
                            } else if ($firstHeader == 1 && $choice == "department") {
                                $firstHeader++;
                                echo "<h2> Department Questions<br> </h2>";
                                $question = 0;
                            } else if ($firstHeader == 2 && $choice == "instructor") {
                                $firstHeader++;
                                echo "<h2> Instructor Questions<br> </h2>";
                                $question = 0;
                            }
                        } else {
                            if ($first == 1) {
                                $first++;
                                $question++;
                                echo "Q" . $question . ": " . $choice . "<br>";
                            } else {
                                echo "" . $choice . "<br>";
                            }
                        }
                    }
                    echo "<br>";
                }
                echo "<button type = 'submit' name = 'backButton'>Back</button> </form>";


        ?>   

        <?php
            } else if ($_SESSION["PID"] == 2) {  
                if (isset($_POST["backButton"])) {
                    header("LOCATION:main.php");
                    return;
                }  
                echo "<h1>Survey Stats for ". $_SESSION["CID"] ."<br> </h1>";
        ?>

        <table>
            <tr>
            <th>Number of Surveys</th>
            <th>Number of Students</th>
            <th>Response Rate</th>
            </tr>
        
        <?php
                $dbh = connectDB();
                $statement = $dbh->prepare("select count(*) from (select surveyNum, sID from answers where sID = :cid group by surveyNum, sID) as t1");
                $statement->bindParam(":cid", $_SESSION["CID"]);
                $result = $statement->execute();
                $numSurvey = $statement->fetch();
                
                $statement = $dbh->prepare("select count(cID) from takes where cID = :cid group by cID");
                $statement->bindParam(":cid", $_SESSION["CID"]);
                $result = $statement->execute();
                $numStudents = $statement->fetch();            
                $dbh = null;

                echo "<tr>";
                echo "<td>" . $numSurvey[0] . "</td>";
                echo "<td>" . $numStudents[0] . "</td>";
                echo "<td>" . ($numSurvey[0] / $numStudents[0]) * 100 . "</td>";
                echo "</tr>";     
        ?>

        </table>

        <?php
                $dbh = connectDB();
                $statement = $dbh->prepare("call result(:cid)");
                $statement->bindParam(":cid", $_SESSION["CID"]);
                $result = $statement->execute();
                $surveyResults = $statement->fetchAll();           
                $dbh = null;

                $universityQ = array();
                $departmentQ = array();
                $instructorQ = array();
                foreach ($surveyResults as $row) {
                    $qID = $row["Question"];
                    $section = $row["Section"];

                    if ($section == "university") {
                        if (!isset($universityQ[$qID])) {
                            $universityQ[$qID] = array();
                            $universityQ[$qID][] = $row["Question"];
                            $universityQ[$qID][] = $row["Question Text"];
                        }
                        $universityQ[$qID][] = $row["Response Option"];
                        $universityQ[$qID][] = $row["Choice Text"];
                        $universityQ[$qID][] = $row["Frequency"];
                        $universityQ[$qID][] = $row["Percent"];
                    } else if ($section == "department") {
                        if (!isset($departmentQ[$qID])) {
                            $departmentQ[$qID] = array();
                            $departmentQ[$qID][] = $row["Question"];
                            $departmentQ[$qID][] = $row["Question Text"];
                        }
                        $departmentQ[$qID][] = $row["Response Option"];
                        $departmentQ[$qID][] = $row["Choice Text"];
                        $departmentQ[$qID][] = $row["Frequency"];
                        $departmentQ[$qID][] = $row["Percent"];
                    } else if ($section == "instructor") {
                        if (!isset($instructorQ[$qID])) {
                            $instructorQ[$qID] = array();
                            $instructorQ[$qID][] = $row["Question"];
                            $instructorQ[$qID][] = $row["Question Text"];
                        }
                        $instructorQ[$qID][] = $row["Response Option"];
                        $instructorQ[$qID][] = $row["Choice Text"];
                        $instructorQ[$qID][] = $row["Frequency"];
                        $instructorQ[$qID][] = $row["Percent"];
                    }
                }

                echo "<h2> University Questions<br> </h2>";
             
                $Question = 1;
                foreach ($universityQ as $question) {
                    $questionID = $question[0];
                    $questionText = $question[1];
                    echo "<h3> Q" . $Question . ": " . $questionText . "</h3>";
                    echo "<table>";
                    echo "<tr><th>Response Option</th><th>Choice Text</th><th>Frequency</th><th>Percent</th></tr>";
                    $i = 2;
                    while ($i < count($question)) {
                        echo "<tr>";
                        echo "<td>" . $question[$i] . "</td>";
                        echo "<td>" . $question[$i+1] . "</td>";
                        echo "<td>" . $question[$i+2] . "</td>";
                        echo "<td>" . $question[$i+3] . "</td>";
                        echo "</tr>";
                        $i += 4;
                    }
                    echo "</table>";
                    $Question++;
                }

                echo "<h2> Department Questions<br> </h2>";
             
                $Question = 1;
                foreach ($departmentQ as $question) {
                    $questionID = $question[0];
                    $questionText = $question[1];
                    echo "<h3> Q" . $Question . ": " . $questionText . "</h3>";
                    echo "<table>";
                    echo "<tr><th>Response Option</th><th>Choice Text</th><th>Frequency</th><th>Percent</th></tr>";
                    $i = 2;
                    while ($i < count($question)) {
                        echo "<tr>";
                        echo "<td>" . $question[$i] . "</td>";
                        echo "<td>" . $question[$i+1] . "</td>";
                        echo "<td>" . $question[$i+2] . "</td>";
                        echo "<td>" . $question[$i+3] . "</td>";
                        echo "</tr>";
                        $i += 4;
                    }
                    echo "</table>";
                    $Question++;
                }

                echo "<h2> Instructor Questions<br> </h2>";
             
                $Question = 1;
                foreach ($instructorQ as $question) {
                    $questionID = $question[0];
                    $questionText = $question[1];
                    echo "<h3> Q" . $Question . ": " . $questionText . "</h3>";
                    echo "<table>";
                    echo "<tr><th>Response Option</th><th>Choice Text</th><th>Frequency</th><th>Percent</th></tr>";
                    $i = 2;
                    while ($i < count($question)) {
                        echo "<tr>";
                        echo "<td>" . $question[$i] . "</td>";
                        echo "<td>" . $question[$i+1] . "</td>";
                        echo "<td>" . $question[$i+2] . "</td>";
                        echo "<td>" . $question[$i+3] . "</td>";
                        echo "</tr>";
                        $i += 4;
                    }
                    echo "</table>";
                    $Question++;
                }
                
                $dbh = connectDB();
                $statement = $dbh->prepare("select answers.surveyNum as Survey, questions.section as Section, questions.qID as Question, questions.description as 'Question Text', choices.description as Response from answers join questions on answers.qID = questions.qID join choices on answers.chID = choices.chID and answers.qID = choices.qID where answers.sID = :cid order by answers.surveyNum, questions.section, questions.qID");
                $statement->bindParam(":cid", $_SESSION["CID"]);
                $result = $statement->execute();
                $totalResults = $statement->fetchAll();           
                $dbh = null;
                
                echo "<h2> All Individual Survey Responses for " . $_SESSION["CID"] . "<br> </h2>";
                echo "<table>";
                echo "<tr><th>Survey</th><th>Section</th><th>Question</th><th>Question Text</th><th>Response</th></tr>";                
                
                foreach ($totalResults as $rows) {
                    echo "<tr>";
                    echo "<td>" . $rows[0] . "</td>";
                    echo "<td>" . $rows[1] . "</td>";
                    echo "<td>" . $rows[2] . "</td>";
                    echo "<td>" . $rows[3] . "</td>";
                    echo "<td>" . $rows[4] . "</td>";
                    echo "</tr>";
                }
                echo "</table>";

                echo "<form method = post action = instructor.php>";
                echo "<button type = 'submit' name = 'backButton'>Back</button> </form>";

            } else if ($_SESSION["PID"] == 3) {    
       
            }
        ?>
        
    </body>
</html>
