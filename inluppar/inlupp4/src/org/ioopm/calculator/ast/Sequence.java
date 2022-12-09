package org.ioopm.calculator.ast;

<<<<<<< HEAD
public class Sequence {
    
=======
import java.util.ArrayList;

public class Sequence extends SymbolicExpression{
   public ArrayList<SymbolicExpression> list = new ArrayList<>();

    // public Sequence(){
    //     this.list = new ArrayList<SymbolicExpression>();
    // }

    // @Override
    public SymbolicExpression accept(Visitor v) {
        return v.visit(this);
    }


   @Override
    public String toString(){
        String temp = "";
        for (SymbolicExpression r : this.list) {
            temp += r + "\n";
        }
        return temp;
    }

>>>>>>> 82d63ad6a7feb43e2cf38c132a031c5ef400fc9c
}
