package org.ioopm.calculator.ast;

public abstract class Binary extends SymbolicExpression {
    protected SymbolicExpression lhs = null;
    protected SymbolicExpression rhs = null;

    public Binary(SymbolicExpression lhs, SymbolicExpression rhs) {
        super();
        this.lhs = lhs;
        this.rhs = rhs;
    }

    public String toString() {
        if (this.prio > this.rhs.prio && this.prio > this.lhs.prio)
        {
            return "(" + String.valueOf(this.lhs) + ")" + " " + this.getName() + " " + "(" + String.valueOf(this.rhs)+ ")";
        }
        
        else if (this.prio > this.rhs.prio)
        {
            return  String.valueOf(this.lhs) + " " + this.getName() + " " + "(" + String.valueOf(this.rhs)+ ")";
        }
        else if (this.prio > this.lhs.prio)
        {
            return "(" + String.valueOf(this.lhs) + ")" + " " + this.getName() + " " + String.valueOf(this.rhs);
        }
        else
        {
            return String.valueOf(this.lhs) + " " + this.getName() + " " + String.valueOf(this.rhs);
        }
        }
    
    public boolean equals(Object other) {
        if (other instanceof Binary) {
            return this.equals((Binary) other);
        } else {
            return false;
        }
    }

    public boolean equals(Binary other) {
        /// access a private field of other!
        return (this.getName().equals(other.getName()) && lhs.equals(other.lhs) && this.rhs.equals(other.rhs));
    }

}