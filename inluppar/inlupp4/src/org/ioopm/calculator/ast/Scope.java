package org.ioopm.calculator.ast;

public class Scope extends SymbolicExpression{
    protected SymbolicExpression arg;

    public Scope(SymbolicExpression n){
        super();
        this.arg = n;
        prio = 100;
    }

    public String toString(){
       return this.arg.toString();
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}
