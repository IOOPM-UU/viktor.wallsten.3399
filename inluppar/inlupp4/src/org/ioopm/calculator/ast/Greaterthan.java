package org.ioopm.calculator.ast;

public class Greaterthan extends Binary {
    
    public Greaterthan(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs,lhs);
        prio = 30; 
    }

    public String getName() {
        return ">";
    }

   public boolean equals(Object other){
    if (other instanceof Greaterthan){
        Greaterthan gt = (Greaterthan) other;
        return this.equals(gt);
    }
    return false;
   }
   
   public boolean equals(Greaterthan gt){
    return this.lhs.equals(gt.lhs) && this.rhs.equals(gt.rhs);
   }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}
