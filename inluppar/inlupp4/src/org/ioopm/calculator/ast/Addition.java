package org.ioopm.calculator.ast;

public class Addition extends Binary{

    public Addition(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs, lhs);
        prio = 50;
    }
    
    public String getName() {
        return "+";
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
            double plus = argl.getValue() + argr.getValue();
            return new Constant(plus);
        } 
        return new Addition(argl, argr);
    }
}


