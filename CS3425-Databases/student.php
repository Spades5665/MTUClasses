<html>
    <body>
        
        <?php
            require "db.php";
            session_start();
            if ($_SESSION["SID"] == 1) {
                if (isset($_POST["backButton"])) {
                    header("LOCATION:main.php");
                    return;
                }

                $dbh = connectDB();
                $statement = $dbh->prepare("select sAccount from student where sName = :username");
                $statement->bindParam(":username", $_SESSION["username"]);
                $result = $statement->execute();
                $row = $statement->fetch();

                $statement = $dbh->prepare("call assign_student(:CID, :SID)");
                $statement->bindParam(":CID", $_SESSION["CID"]);
                $statement->bindParam(":SID", $row[0]);
                $result = $statement->execute();

                echo '<p>You have been added to '. $_SESSION["CID"];
        ?>   

        <form method = post action = student.php>
            <button type = "submit" name = "backButton">Back</button>
        </form>

        <?php
            } else if ($_SESSION["SID"] == 2) {
                
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
                    
                    $survey[$qID][] = $row["chID"];
                    $survey[$qID][] = $row["cDescription"];
                }

                $firstHeader = 0;
                $question = 0;
                $counter = 0;
                $choiceID = 0;
                echo "<form method = 'post' action = 'student.php'>";
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
                            } else if ($counter % 2 == 0) {
                                $choiceID = $choice;
                            } else if ($counter % 2 == 1) {
                                echo "<input type='radio' name='" . $qID . "' value='" . $choiceID . "' required>" . $choice . "<br>";
                            }
                        }

                        if ($counter == 0) {
                            $counter = 1;
                        } else if ($counter == 1) {
                            $counter = 0;
                        }
                    }
                    echo "<br>";
                }
                echo "<button type = 'submit' name = 'submitSurveyButton'>Submit</button> </form>";

                if (isset($_POST["submitSurveyButton"])) {
                    $dbh = connectDB();

                    $statement = $dbh->prepare("select sAccount from student where sName = :name");
                    $statement->bindParam(":name", $_SESSION["username"]);
                    $result = $statement->execute();
                    $sID = $statement->fetch();
                    
                    $statement = $dbh->prepare("update takes set sCompleted = now() where sAccount = :acct and cID = :CID");
                    $statement->bindParam(":acct", $sID[0]);
                    $statement->bindParam(":CID", $_SESSION["CID"]);
                    $result = $statement->execute();

                    $statement = $dbh->prepare("select count(*) from takes where sCompleted is not null");
                    $result = $statement->execute();
                    $surveyNum = $statement->fetch();                  
                    
                    foreach ($survey as $qID => $choices) {
                        if (isset($_POST[$qID])) {
                            $selectedChoice = $_POST[$qID];
                            $statement = $dbh->prepare("insert into answers values (:surveyNum, :cid, :qid, :chid)");
                            $statement->bindParam(":surveyNum", $surveyNum[0]);
                            $statement->bindParam(":cid", $_SESSION["CID"]);
                            $statement->bindParam(":qid", $qID);
                            $statement->bindParam(":chid", $selectedChoice);
                            $result = $statement->execute();
                        }
                    }

                    $dbh = null;
                    
                    header("LOCATION:main.php");
                    return;
                }
                
        ?>

        <?php        
            }
        ?>
        
    </body>
</html>
