package org.ioopm.calculator.ast;

public class Division extends Binary{

    public Division (SymbolicExpression lhs, SymbolicExpression rhs){
        super(lhs,rhs);
        prio = 100;
    }

    public String getName() {
        return "/";
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
