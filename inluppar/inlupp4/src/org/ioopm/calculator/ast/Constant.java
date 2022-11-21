package org.ioopm.calculator.ast;

public class Constant extends Atom{
    private double value;
    
    public Constant(Double value){
        super();
        prio = 200;
        this.value = value;
    }

    public Constant (int value){
        super();
        prio = 200;
        this.value = value;
    }

    public Boolean isConstant() {
        return true;
    }

    public double getValue(){
        return this.value;
    }

   public String toString() {
        return String.valueOf(this.value);
    }

    public boolean equals(Object other) {
        if (other instanceof Constant) {
            return this.equals((Constant) other);
        } else {
            return false;
        }
    }

    public boolean equals(Constant other) {
        return this.value == other.value;
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

    public SymbolicExpression eval(Environment vars){
        return new Constant (this.value);
    }
}

