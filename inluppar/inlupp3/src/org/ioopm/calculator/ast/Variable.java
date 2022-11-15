package org.ioopm.calculator.ast;

public class Variable extends Atom{
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

    public SymbolicExpression eval(Environment vars) {
        Variable test = new Variable(this.c);
        if(vars.get(test) != null){
            return vars.get(test).eval(vars);
        }
        return new Variable(this.c);
    }

    @Override
    public int hashCode(){
        return this.c.toString().hashCode();
    }

    public boolean isCommand(){
        return true;
    }
}
