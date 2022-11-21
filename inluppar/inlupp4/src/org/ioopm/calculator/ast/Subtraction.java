package org.ioopm.calculator.ast;

public class Subtraction extends Binary{

    public Subtraction(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs, lhs);
        prio = 50;
    }

    public String getName() {
        return "-";
    }

    public int getPriority() {
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
