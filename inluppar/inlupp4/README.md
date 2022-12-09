# Inlupp 4: Calculator and Parser
Fredrik Forsman & Viktor Wallsten

# Program Description

This programs simulates a symbolic calculator. This calculator allows the user to evaluate basic expressions with numeric values, assigning values to variables, user defined functions aswell as define conditional expressions.

# Usage

Generally, failure is dealt with by throwing and catching controlled exceptions when, for example, trying to assign a new value to a named constant or trying to reassign an already assigned variable. 

For running the interactive user interface of the program, complie the program by the command "make all" and then run the program by the command "make run". The program will ask you to enter an expression and if it is a valid expression, the program will print the evaluated expression in the terminal. Otherwise you will recieve an error message and will be asked to enter a new expression.

There are a few commands that you can use in the calculator. Type "Vars" to view all the assigned variables and their values in the terminal. Type "Clear" to clear all the assigned variables and to make them avaliable to be assigned to new values again. Finally, type "Quit" to quit the loop of the calculator asking you to enter an expression and now you will see all the entered expressions, all the evaluated expressions and all the fully evaluated expressions for this round of running the calculator. 

Inorder to define a new function usee the keyword "function" followed by the name of the function with the accompanying arguments. Then define the functionbody and conclude the functionbody with "end". inorder to call a function write the name of a function with the appropriate arguments.