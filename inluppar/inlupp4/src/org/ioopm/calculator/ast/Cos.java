package org.ioopm.calculator.ast;

public class Cos extends Unary{

    public Cos(SymbolicExpression arg){
        super(arg);
    }

    public String getName() {
        return "cos";
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
