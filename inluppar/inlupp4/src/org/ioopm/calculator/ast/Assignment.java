package org.ioopm.calculator.ast;

public class Assignment extends Binary{

    public Assignment (SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs, lhs);
    }

    public String getName() {
        return "=";
    }

    public String toString(){
        return this.getName();
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

}