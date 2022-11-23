package org.ioopm.calculator.ast;

public class Addition extends Binary{
    double prio;

    public Addition(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs, lhs);
        this.prio = 50;
    }
    
    public String getName() {
        return "+";
    }

    public double getPriority() {
        return this.prio;
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


