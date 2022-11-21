package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression{
    protected SymbolicExpression arg;

    public Unary(SymbolicExpression un){
        super();
        this.arg = un;
    }

    public String toString() {
        /// Note how the call to toString() is not necessary
        return this.getName() + " " + String.valueOf(this.arg);
    }

    public boolean equals(Object other) {
        if (other instanceof Unary) {
            return this.equals((Unary) other);
        } else {
            return false;
        }
    }

    public boolean equals(Unary other) {
        /// access a private field of other!
        return (this.getName().equals(other.getName()) && this.arg == other.arg);
    }
}
