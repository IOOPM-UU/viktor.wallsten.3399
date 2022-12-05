package org.ioopm.calculator.ast;

import java.util.ArrayList;

public class FunctionDeclaration extends SymbolicExpression {
    public String name;
    public ArrayList<Variable> parameters = new ArrayList<>();
    public Sequence body;
    
    public FunctionDeclaration(){
        super();
        this.name = "hej";
        this.body = new Sequence();

    }
    public FunctionDeclaration(String name, ArrayList<Variable> parameters, Sequence body){
        super();
        this.name = name;
        this.parameters = parameters;
        this.body = body;
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) {
        // TODO Auto-generated method stub
        return v.visit(this);
    }
    
    @Override
    public String toString() {
        return "\n" + this.name.toString() + this.parameters.toString() + "\n" + this.body.toString();
    }

}
