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

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

}
