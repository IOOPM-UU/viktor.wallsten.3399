package org.ioopm.calculator.ast;

public class Conditonal extends SymbolicExpression {
    SymbolicExpression arg;
    Scope s1;
    Scope s2;

    public Conditonal(SymbolicExpression arg, SymbolicExpression s1, SymbolicExpression s2){
        super();
        if ( arg instanceof Greaterthan || arg instanceof GreaterthanEquals || arg instanceof Lessthan || arg instanceof Lessthanequals || arg instanceof Eq){
            this.arg = arg;
            if(s1 instanceof Scope || s2 instanceof Scope){
                this.s1 = (Scope) s1;
                this.s2 = (Scope) s2;
            } else{
                throw new IllegalExpressionException("only scopes allowed");
            }
        } 
        else{
            throw new IllegalExpressionException("Only if statments are allowed");
        }
    }

    @Override
    public String toString(){
        return this.arg.toString();
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}