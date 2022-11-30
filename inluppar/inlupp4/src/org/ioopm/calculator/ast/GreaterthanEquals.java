package org.ioopm.calculator.ast;

public class GreaterthanEquals extends Binary{
    
    public GreaterthanEquals(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs,lhs);
        prio = 30; 
    }

    public String getName() {
        return ">=";
    }

    public int getPriority() {
        return this.prio;
    }

    public boolean equals(Object other){
        if (other instanceof GreaterthanEquals){
            GreaterthanEquals gt = (GreaterthanEquals) other;
            return this.equals(gt);
        }
        return false;
       }
       
       public boolean equals(GreaterthanEquals gt){
        return this.lhs.equals(gt.lhs) && this.rhs.equals(gt.rhs);
       }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}
