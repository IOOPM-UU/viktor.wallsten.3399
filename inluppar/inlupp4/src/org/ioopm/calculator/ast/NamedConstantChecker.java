package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class NamedConstantChecker implements Visitor {
    private ArrayList<Assignment> asList = new ArrayList<Assignment>();

    public boolean check(SymbolicExpression n){
            asList.clear();
            n.accept(this);
            if (this.asList.size() > 0) {
                System.out.println("Error, assignments to named constants: ");
                StringBuilder sb = new StringBuilder();
                for(int i = 0; asList.size() < i; i++){
                    sb.append(asList.get(i).toString());
                    sb.append('\n');
                }
                return false;
        }
        return true;
    }

    public SymbolicExpression visit(Addition a) {
        a.lhs.accept(this);
        a.rhs.accept(this);
        return a; 
    }

    public SymbolicExpression visit(Assignment a) {
        a.rhs.accept(this);
        if (a.rhs.isNamedConstant()) { 
            int index = asList.size();
            asList.add(index, a);
        }
        return a;
    }

    @Override
    public SymbolicExpression visit(Constant n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Cos n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Division a) {
        a.lhs.accept(this);
        a.rhs.accept(this);        
        return a;
    }

    @Override
    public SymbolicExpression visit(Exp n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Log n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Multiplication a) {
        a.lhs.accept(this);
        a.rhs.accept(this);        
        return a;
    }

    @Override
    public SymbolicExpression visit(Negation n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Quit n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Sin n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Subtraction a) {
        a.lhs.accept(this);
        a.rhs.accept(this);        
        return a;
    }

    @Override
    public SymbolicExpression visit(Variable n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Vars n) {
        return n;
    }

    @Override
    public SymbolicExpression visit(Clear n) {
        return n;
    }

    public SymbolicExpression visit(Scope n){
        return n;
    }

}