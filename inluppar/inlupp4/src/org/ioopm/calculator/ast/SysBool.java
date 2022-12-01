package org.ioopm.calculator.ast;

public class SysBool extends Atom {
    private boolean value;

    public SysBool(Boolean value){
        this.value = value;
    }

    public boolean equals(SysBool other){
        return this.value == other.value;
    }

    public boolean equals(Object other){
        if (other instanceof SysBool){
            SysBool bool = (SysBool) other;
            return this.equals(bool);
        }
        return false;
       }
    
    @Override
    public boolean getBool(){
        return this.value;
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }

}
