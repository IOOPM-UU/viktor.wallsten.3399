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

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression argl = this.lhs.eval(vars);
    SymbolicExpression argr = this.rhs.eval(vars);
    
    if(argr.getValue() == 0){
        throw new IllegalExpressionException("illegal divition with zero");
    }
    else if (argl.isConstant() && argr.isConstant()) {
            double divide = argl.getValue() / argr.getValue();
            return new Constant(divide);
        } 
        return new Division(argl, argr);
    }
}
