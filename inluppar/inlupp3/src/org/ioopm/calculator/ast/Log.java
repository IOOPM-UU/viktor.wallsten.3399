package org.ioopm.calculator.ast;

public class Log extends Unary{

    public Log(SymbolicExpression un){
        super(un);
    }

    public String getName() {
        return "log";
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
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }
}
