package org.ioopm.calculator.ast;

public class Eq extends Binary {

    public Eq(SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs,lhs);
        prio = 50; 
    }

    public String getName() {
        return "==";
    }

    public int getPriority() {
        return this.prio;
    }
    public String toString(){
        return super.toString();
    }
/* 
    public boolean equals(Object other){
        if (other instanceof Eq){
            Eq gt = (Eq) other;
            return this.equals(gt);
        }
        return false;
       }
       
       public boolean equals(Eq gt){
        return this.lhs.equals(gt.lhs) && this.rhs.equals(gt.rhs);
       }
*/
    public boolean equals(Object other) {
        return super.equals(other);
    }
    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
    
}
