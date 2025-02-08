#!/bin/bash

FILE1="test_cat.txt"
FILE2="test_grep1.txt"

diff <(../cat/s21_cat $FILE1) <(cat $FILE1)
diff <(../cat/s21_cat -e $FILE1) <(cat -e $FILE1)
diff <(../cat/s21_cat -b $FILE1) <(cat -b $FILE1)
diff <(../cat/s21_cat -n $FILE1) <(cat -n $FILE1)
diff <(../cat/s21_cat -s $FILE1) <(cat -s $FILE1)
diff <(../cat/s21_cat -t $FILE1) <(cat -t $FILE1)
diff <(../cat/s21_cat -e -n $FILE1) <(cat -e -n $FILE1)
diff <(../cat/s21_cat --number-nonblank $FILE1) <(cat --number-nonblank $FILE1)
diff <(../cat/s21_cat --squeeze-blank -n $FILE1 $FILE2) <(cat --squeeze-blank -n $FILE1 $FILE2)
diff <(../cat/s21_cat --number $FILE1) <(cat --number $FILE1)
diff <(../cat/s21_cat -ebnst $FILE1) <(cat -ebnst $FILE1)