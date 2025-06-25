<html>
    <body>
        <?php
            function connectDB() {
                $config = parse_ini_file("db.ini");
                $dbh = new PDO($config['dsn'], $config['username'], $config['password']);
                $dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                return $dbh;
            }
            
            function authenticate($user, $passwd, $prof) {
                try {
                    $dbh = connectDB();
                    if ($prof == "student") {
                        $statement = $dbh->prepare("SELECT count(*) FROM student where sName = :username and sPassword = sha2(:passwd,256) ");
                    } else if ($prof == "instructor") {
                        $statement = $dbh->prepare("SELECT count(*) FROM instructor where iName = :username and iPassword = sha2(:passwd,256) ");
                    } else {
                        print "Error!<br/>";
                        die();
                    }
                    
                    $statement->bindParam(":username", $user);
                    $statement->bindParam(":passwd", $passwd);
                    $result = $statement->execute();
                    $row=$statement->fetch();
                    $dbh=null;
                    return $row[0];
                } catch (PDOException $e) {
                    print "Error!" . $e->getMessage() . "<br/>";
                    die();
                }
            }

            function i_get_courses($user)
            {
                try
                {
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select course.cID, course.title, course.credits from course natural join instructor where instructor.iName = :username");
                    $statement->bindparam(":username", $user);
                    $statement->execute();
                    return $statement->fetchAll();
                    $dbh = null;
                }
                catch (PDOException $e)
                {
                    print "Error!" . $e->getMessage() . "<br/>";
                    die();
                }
            }

            function s_get_courses($user)
            {
                try
                {
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select course.cID, course.title, course.credits, instructor.iName, takes.sCompleted from course natural join takes natural join student natural join instructor where student.sName = :username");
                    $statement->bindparam(":username", $user);
                    $statement->execute();
                    return $statement->fetchAll();
                    $dbh = null;
                }
                catch (PDOException $e)
                {
                    print "Error!" . $e->getMessage() . "<br/>";
                    die();
                }
            }

            function s_get_not_courses($user)
            {
                try
                {
                    $dbh = connectDB();
                    $statement = $dbh->prepare("select * from (select course.cID, course.title, course.credits, instructor.iName, course.department from course natural join instructor) t1 natural join (select cID from course where cID not in (select takes.cID from takes natural join student where student.sName = :username)) t2");
                    $statement->bindparam(":username", $user);
                    $statement->execute();
                    return $statement->fetchAll();
                    $dbh = null;
                }
                catch (PDOException $e)
                {
                    print "Error!" . $e->getMessage() . "<br/>";
                    die();
                }
            }

            

            

            /*
            function get_accounts($user) {
                //connect to database
                //retrieve the data and display
                try {
                    $dbh = connectDB();
                    $statement = $dbh->prepare("SELECT account_no, balance name FROM lab5_accounts where username = :username");
                    $statement->bindParam(":username", $user);
                    $statement->execute();
                    return $statement->fetchAll();
                    $dbh = null;
                } catch (PDOException $e) {
                    print "Error!" . $e->getMessage() . "<br/>";
                    die();
                }
            }

            function transfer($from, $to, $amount, $user) {
                try {
                    $dbh = connectDB();
                    $dbh->beginTransaction();
                    // check if there are enough balance in the from account
                    $statement = $dbh->prepare("select balance from lab5_accounts where account_no=:from ");
                    $statement->bindParam(":from", $from);
                    $result = $statement->execute();
                    $row = $statement->fetch();
                    if ($row) {
                        $currentBalance = $row[0];
                        if ($currentBalance < $amount) {
                            echo "Not enough balance in $from";
                            $dbh->rollBack();
                            $dbh=null;
                            return;
                        }
                    } else {
                        echo "Account $from does not exist";
                        $dbh->rollBack();
                        $dbh=null;
                        return;
                    }
                    $statement = $dbh->prepare("update lab5_accounts set balance = balance - :amount " . "where account_no=:from");
                    $statement->bindParam(":amount", $amount);
                    $statement->bindParam(":from", $from);
                    $result = $statement->execute();
                    $statement = $dbh->prepare("update lab5_accounts set balance = balance + :amount " . "where account_no= :to");
                    $statement->bindParam(":amount", $amount);
                    $statement->bindParam(":to", $to);
                    $result = $statement->execute();
                    echo "Money has been transfered successfully";
                    $dbh->commit();
                } catch (Exception $e) {
                    echo "Failed: " . $e->getMessage();
                    $dbh->rollBack();
                }
                $dbh=null;
            }
            */
        ?>
    </body>
</html>