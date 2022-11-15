package org.ioopm.calculator.ast;

public class Multiplication extends Binary{

    public Multiplication (SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs, lhs);
        prio = 100;
    }

    public String getName() {
        return "*";
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

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression argl = this.lhs.eval(vars);
    SymbolicExpression argr = this.rhs.eval(vars);

    if (argl.isConstant() && argr.isConstant()) {
            double mult = argl.getValue() * argr.getValue();
            return new Constant(mult);
        } 
        return new Multiplication(argl, argr);
    }
}
