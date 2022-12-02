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
    final NamedConstantChecker checker = new NamedConstantChecker();
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    final ReassignmentChecker r_checker = new ReassignmentChecker();

    while(eventloop){
        System.out.println("Please enter an expression");
        try{
            String input = System.console().readLine();
            final SymbolicExpression topLevel = p.parse(input, e); 

            if (!checker.check(topLevel)) {
                
            }
            if (topLevel instanceof FunctionDeclaration){
                Sequence hej = new Sequence(null);
                topLevel.body = hej;
            }
            if (!r_checker.check(topLevel)) {
                System.out.print("shit is working");
            }

            else{
                final SymbolicExpression result = evaluator.evaluate(topLevel, e);
                enteredExpressions++;
                if(result instanceof Command){
                    enteredExpressions--;
                    if(result instanceof Quit)
                    {
                        eventloop = false;
                        System.out.println("Total expresxsions entered: " + enteredExpressions);
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
                        System.out.println(e);
                    }
                }
                else{
                    SymbolicExpression awnser = evaluator.evaluate(result, e);
                    System.out.println(awnser);
                    evaluatedExpressions++;
                    if(awnser.isConstant()){
                        fullyEvaluated++;
                    }
                }
            }
        }catch(Exception ex){
            System.out.println(ex.toString());
        }
    }
    
}
}
