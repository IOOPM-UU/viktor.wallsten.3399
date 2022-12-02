package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class Sequence extends ArrayList{
    private ArrayList<SymbolicExpression> list;

    public Sequence(){
        this.list = new ArrayList<SymbolicExpression>();
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        // TODO Auto-generated method stub
        return null;
    }
}
