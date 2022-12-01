package org.ioopm.calculator.ast;

public abstract class SymbolicExpression {
    public int prio;

    public SymbolicExpression(){
        this.prio = 0;
    }

    public Boolean isConstant() {
        return false;
    }

    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator");
    }

    public int getPriority() {
        return this.prio;
    }


    public boolean isCommand(){
        return false;
    }

    public Boolean isNamedConstant(){
        return false;
    }

    public Boolean isVariable(){
        return false;
    }

    public boolean getBool(){
        return false;
    }

    public double getValue(){
        throw new RuntimeException("getValue() called on a non-constant expression");
    }
    
    public boolean equals(Object other) {
        if (other instanceof Constant) {
            return this.equals((Constant) other);
        }
        else if (other instanceof Variable) {
            return this.equals((Variable) other);
        }
        else if (other instanceof Binary) {
            return this.equals((Binary) other);
        }
        else if (other instanceof Unary) {
            return this.equals((Unary) other);
        }
        else {
            return false;
        }
    }

    public abstract SymbolicExpression accept(Visitor v);
}
