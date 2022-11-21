package org.ioopm.calculator.ast;

public class Exp extends Unary{
    
    public Exp(SymbolicExpression arg){
        super(arg);
        prio = 150;
    }

    public String getName() {
        return "^";
    }

    public int getPriority(){
        return this.prio;
    }

    public String toString(){
        return super.toString();
    }

    public boolean equals(Object other) {
        return super.equals(other);
    }

    public SymbolicExpression eval(Environment vars) {
    SymbolicExpression arg = this.arg.eval(vars);
    
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }    
}
