package org.ioopm.calculator.ast;

public class Scope extends SymbolicExpression{
    private SymbolicExpression n;

    public Scope(SymbolicExpression n){
        super();
        this.n = n;
    }

    public String toString(){
       return this.n.toString();
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}
