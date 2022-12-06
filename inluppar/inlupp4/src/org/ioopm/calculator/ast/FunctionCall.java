package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionCall extends SymbolicExpression {
    public String name;
    public ArrayList<SymbolicExpression> list;
    public FunctionDeclaration funcDec;


    public FunctionCall(String name, ArrayList<SymbolicExpression> list, FunctionDeclaration funcDec){
        this.name = name;
        this.list = list;
        this.funcDec = funcDec;
    }


    @Override
    public SymbolicExpression accept(Visitor v) {
        // TODO Auto-generated method stub
        return v.visit(this);
    }
}
