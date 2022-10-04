HOW TO COMPILE

In order to compile the hash table,linked list and iterator files write "make unit_tests"
in order to run tests and check for memory leak write "make memtest"
in order to run coverage test write "make cov"

TESTCOVERAGE
Using lcov we can conclude that 98.9% of the lines are executed and 100% of the functions are executed.
The reason that 100% of the lines are not being executed is because of some lines for errors which will not be executed if all the tests execute correctly.

HANDELING FAILIURES
Failiures are handeld with the type bool, e.g in the function ioopm_hash_table_lookup, if the key was succesfully found the function will return true otherwise false. To get the value mapped to the key we added a new parameter to the function, which is a pointer. When the function is succesfull the  pointer value will take the value that was mapped to the key.

Freq-count on a 10k long textfile
1. key_eqiv_string
2. ioopm_hash_table_any
3. string_eq

freq-count on a 1k long textfile
1. key_eqiv_string
2. string_eq
3. string_sum_hash

freq-count on small
1. key_eqiv_string
2. string_sum_hash
3. string_eq

Q/A
Q1 Are the top 3 functions in your code consistent across the inputs? Why? Why not?
A1 Yes, since all the files where textfiles of different sizes it makes sense that it is the same functions doing the job.

Q2 Is there some kind of trend? (Possibly several.)
A2 Yes, key_eqiv_string was always the most used function and string_eq was awlays in the top 3

Q3 Do the results correspond with your expectations?
A3 No I thought that insert or lookup would be in the top 3 most used functions, at least in the smaller textfiles.

Q4 Based on these results, do you see a way to make your program go faster?
A4 Not at the moment
