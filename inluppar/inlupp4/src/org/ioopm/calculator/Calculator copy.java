package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;


public class Calculator {

public static void main(String[] args) {

    Boolean eventloop = true;

    final CalculatorParser p = new CalculatorParser();

    final Environment e = new Environment();

    int enteredExpressions = 0;
    int evaluatedExpressions = 0;
    int fullyEvaluated = 0;

    while(eventloop){
        System.out.println("Please enter an expression");
        try{
            String input = System.console().readLine();
            SymbolicExpression result = p.parse(input, e);
            enteredExpressions++;
            if(result instanceof Command){
                enteredExpressions--;
                if(result instanceof Quit)
                {
                    eventloop = false;
                    System.out.println("Total expressions entered: " + enteredExpressions);
                    System.out.println("Total expressions evaluated: " + evaluatedExpressions);
                    System.out.println("Total expressions fully evaluated: " + fullyEvaluated);
                }
                else if (result instanceof Clear)
                {
                    e.clear();
                    System.out.println("All assigned variables have now been cleared!");
                }
                else if(result instanceof Vars){
                    System.out.println("All variables and values: ");
                    e.print();
                }
            }
            else{
                SymbolicExpression awnser = result.visit(e);
                System.out.println(awnser);
                evaluatedExpressions++;
                if(awnser.isConstant()){
                    fullyEvaluated++;
                }
            }

        }catch(Exception ex){
            System.out.println(ex.toString());
        }
    }
}
}
