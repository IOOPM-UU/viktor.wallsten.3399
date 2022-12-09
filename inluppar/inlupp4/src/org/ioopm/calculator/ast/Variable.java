package org.ioopm.calculator.ast;

public class Variable extends Atom implements Comparable{
    private String c;    

    public Variable(String c) {
        prio = 200;
        this.c = c;
    }

    public String toString() {
        return this.c;
    }

    public boolean equals(Object other) {
    if (other instanceof Variable) {
        return this.equals((Variable) other);
    } else {
        return false;
    }
    }

    public boolean equals(Variable other) {
        /// access a private field of other!
        return this.c.equals(other.c);
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }


    @Override
    public int hashCode(){
        return this.c.toString().hashCode();
    }

    // @Override
    // public boolean isCommand(){
    //     return true;
    // }

    public String getName(){
        return this.toString();
    }

    @Override
    public int compareTo(Object o) {
        Variable v = (Variable) o;
        return (this.c.compareTo(v.c));
    }

    public Boolean isVariable(){
        return true;
    }
}
