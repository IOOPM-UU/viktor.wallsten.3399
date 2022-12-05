package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionCall extends SymbolicExpression {
    public String name;
    public ArrayList<Constant> list;
    public FunctionDeclaration funcDec;


    public FunctionCall(String name, ArrayList<Constant> list, FunctionDeclaration funcDec){
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
