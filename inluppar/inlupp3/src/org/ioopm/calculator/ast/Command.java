package org.ioopm.calculator.ast;

public abstract class Command extends SymbolicExpression{

    public Command(){
    }

    public boolean isCommand(){
        return true;
    }

    @Override
    public SymbolicExpression eval(Environment vars){
        throw new RuntimeException("can't eval a command");  
    }
}
