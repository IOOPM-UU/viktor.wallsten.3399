package org.ioopm.calculator.ast;

public class Log extends Unary{

    public Log(SymbolicExpression un){
        super(un);
    }

    public String getName() {
        return "log";
    }

    public String toString(){
        return super.toString();
    }

    public boolean equals(Object other) {
        return super.equals(other);
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

}
