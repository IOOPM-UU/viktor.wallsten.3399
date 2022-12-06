package org.ioopm.calculator.ast;

<<<<<<< HEAD
public class Sequence {
    
=======
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

>>>>>>> 82d63ad6a7feb43e2cf38c132a031c5ef400fc9c
}
