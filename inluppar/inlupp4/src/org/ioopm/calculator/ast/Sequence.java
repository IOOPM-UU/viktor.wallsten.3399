package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class Sequence extends ArrayList<SymbolicExpression>{
//    private ArrayList<SymbolicExpression> list;

    // public Sequence(){
    //     this.list = new ArrayList<SymbolicExpression>();
    // }

    // @Override
    public SymbolicExpression accept(Visitor v) {
        // TODO Auto-generated method stub
        return v.visit(this);
    }


   @Override
    public String toString(){
        String temp = "";
        for (SymbolicExpression r : this) {
            temp += r + "\n";
        }
        return temp;
    }

}
