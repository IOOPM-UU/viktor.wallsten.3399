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

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

}
