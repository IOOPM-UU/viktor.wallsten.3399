package org.ioopm.calculator.ast;

public class Lessthan extends Binary {
  
    public Lessthan(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs,lhs);
        prio = 30; 
    }

    public String getName() {
        return "<";
    }

    public int getPriority() {
        return this.prio;
    }

    public boolean equals(Object other){
        if (other instanceof Lessthan){
            Lessthan gt = (Lessthan) other;
            return this.equals(gt);
        }
        return false;
       }
       
       public boolean equals(Lessthan gt){
        return this.lhs.equals(gt.lhs) && this.rhs.equals(gt.rhs);
       }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}
