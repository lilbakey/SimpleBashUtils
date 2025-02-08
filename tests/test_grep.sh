#!/bin/bash

FILE1="test_grep2.txt"
FILE2="test_grep1.txt"
FILE3="reg.txt"

diff <(../grep/s21_grep -e hello $FILE1 $FILE2) <(grep -e hello $FILE1 $FILE2)
diff <(../grep/s21_grep -i hello $FILE1 $FILE2) <(grep -i hello $FILE1 $FILE2)
diff <(../grep/s21_grep -v hello $FILE1 $FILE2) <(grep -v hello $FILE1 $FILE2)
diff <(../grep/s21_grep -c hello $FILE1 $FILE2) <(grep -c hello $FILE1 $FILE2)
diff <(../grep/s21_grep -l hello $FILE1 $FILE2) <(grep -l hello $FILE1 $FILE2)
diff <(../grep/s21_grep -n hello $FILE1 $FILE2) <(grep -n hello $FILE1 $FILE2)
diff <(../grep/s21_grep -h hello $FILE1 $FILE2) <(grep -h hello $FILE1 $FILE2)
diff <(../grep/s21_grep -s hello $FILE1 $FILE2) <(grep -s hello $FILE1 $FILE2)

diff <(../grep/s21_grep -e hello $FILE2) <(grep -e hello $FILE2)
diff <(../grep/s21_grep -i hello $FILE2) <(grep -i hello $FILE2)
diff <(../grep/s21_grep -v hello $FILE2) <(grep -v hello $FILE2)
diff <(../grep/s21_grep -c hello $FILE2) <(grep -c hello $FILE2)
diff <(../grep/s21_grep -l hello $FILE2) <(grep -l hello $FILE2)
diff <(../grep/s21_grep -n hello $FILE2) <(grep -n hello $FILE2)
diff <(../grep/s21_grep -h hello $FILE2) <(grep -h hello $FILE2)
diff <(../grep/s21_grep -s hello $FILE2) <(grep -s hello $FILE2)

diff <(../grep/s21_grep -lc "hello" $FILE2) <(grep -lc "hello" $FILE2)
diff <(../grep/s21_grep -iv hello -i $FILE2) <(grep -iv hello -i $FILE2)
diff <(../grep/s21_grep -in hello -i $FILE2) <(grep -in hello -i $FILE2)
diff <(../grep/s21_grep -vh hello $FILE2) <(grep -vh hello $FILE2)
diff <(../grep/s21_grep -ns hello $FILE2) <(grep -ns hello $FILE2)
diff <(../grep/s21_grep -ie hello $FILE2) <(grep -ie hello $FILE2)
diff <(../grep/s21_grep -ince hello -i $FILE2) <(grep -ince hello -i $FILE2)
diff <(../grep/s21_grep -ilh hello -i $FILE2) <(grep -ilh hello -i $FILE2)
diff <(../grep/s21_grep -hc hello $FILE2) <(grep -hc hello $FILE2)


diff <(../grep/s21_grep -vc hel.o $FILE1 $FILE2) <(grep -vc hel.o $FILE1 $FILE2)
diff <(../grep/s21_grep -e he..o -e HELLO -f $FILE3 $FILE1 $FILE2) <(grep -e he..o -e HELLO -f $FILE3 $FILE1 $FILE2)
diff <(../grep/s21_grep -e HELLO -o -vc $FILE1 $FILE2 $FILE3) <(grep -e HELLO -o -vc $FILE1 $FILE2 $FILE3)
