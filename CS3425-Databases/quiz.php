<html>
    <body>
        <?php
            if (isset($_POST["submitButton"])) {
                echo "Your answers are: <br>";
                foreach (array_keys($_POST) as $x) {
                    if ($x != 'submitButton')
                        echo $x .": ". $_POST[$x]. "<br>";
                }
                return;
            }
        ?>
        <form method = post action = quiz.php>
            <p>Q1: The pace of this course<br>
                <input type = "radio" name = "Q1" value = "A"> A: is too slow<br>
                <input type = "radio" name = "Q1" value = "B"> B: is just right<br>
                <input type = "radio" name = "Q1" value = "C"> C: is too fast<br>
                <input type = "radio" name = "Q1" value = "D"> D: I don't know
            </p>
            <p>Q2: The feedback from homework assignment grading<br>
                <input type = "radio" name = "Q2" value = "A"> A: too few<br>
                <input type = "radio" name = "Q2" value = "B"> B: sufficient<br>
                <input type = "radio" name = "Q2" value = "C"> C: I don't know
            </p>
            <p>Q3: Any thing you like about the teaching of this course?<br>
                <textarea name = "Q3"></textarea>
            </p>
            <button type = "submit" name = "submitButton">Submit</button>
        </form>
    </body>
</html>