package org.ioopm.calculator.ast;

public class Sin extends Unary{
    
    public Sin(SymbolicExpression un){
        super(un);
    }

    public String getName() {
        return "sin";
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
        return new Constant(Math.sin(arg.getValue()));
    } else {
        return new Sin(arg);
    }
}
}
