package org.ioopm.calculator.ast;

import java.util.ArrayList;

import javax.naming.spi.DirStateFactory.Result;

public class ReassignmentChecker implements Visitor{
    private ArrayList<String> l_e = new ArrayList<>();
 
    public boolean check(SymbolicExpression n){
        l_e.clear();
        n.accept(this);
        int size = l_e.size();
        for (int j = 0; j < size; j++){
            int acc = 0;
            for (int i = 0; i < size; i++){
                if (0 == l_e.get(j).compareTo(l_e.get(i))){
                    acc++;
                    if (acc > 1){
                        System.out.println("Can't redefine the variable: " + l_e.get(j));
                        return false;
                    }
                }
            }
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
        if (a.rhs.isVariable()) { 
            l_e.add((String) a.rhs.getName());
        }
        return a;
    }

    @Override
    public SymbolicExpression visit(Variable n) {
        return n;
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

    public SymbolicExpression visit(Greaterthan n){   
        return n;
    }
    public SymbolicExpression visit(GreaterthanEquals n){        
        return n;
    }
    public SymbolicExpression visit(Lessthan n){       
        return n;
    }
    public SymbolicExpression visit (Lessthanequals n){     
        return n;
    }
    public SymbolicExpression visit (Eq n){
        return n;
    }
    public SymbolicExpression visit(Conditonal n){
        return n;
    }

    public SymbolicExpression visit(SysBool n){
        return n;
    }
}
