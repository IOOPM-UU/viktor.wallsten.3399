package org.ioopm.calculator.ast;

public class Negation extends Unary{

    public Negation(SymbolicExpression un){
        super(un);
    }

    public String getName() {
        return "-";
    }

    public String toString(){
        return super.toString();
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.arg.eval(vars);
            if (arg.isConstant()) {
                return new Constant((-1) * (arg.getValue()));
            } else {
                return new Negation(arg);
            }
        }
}
