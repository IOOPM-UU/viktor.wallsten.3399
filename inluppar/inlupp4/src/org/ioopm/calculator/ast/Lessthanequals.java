package org.ioopm.calculator.ast;

public class Lessthanequals extends Binary {
    
    public Lessthanequals(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs,lhs);
        prio = 50; 
    }

    public String getName() {
        return ">=";
    }

    public int getPriority() {
        return this.prio;
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
    /* 
    public boolean equals(Object other){
        if (other instanceof Lessthanequals){
            Lessthanequals gt = (Lessthanequals) other;
            return this.equals(gt);
        }
        return false;
       }
       
       public boolean equals(Lessthanequals gt){
        return this.lhs.equals(gt.lhs) && this.rhs.equals(gt.rhs);
       }
*/
}
