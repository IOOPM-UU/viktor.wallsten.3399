package org.ioopm.calculator.ast;

public class NamedConstant extends Atom{
    private String name;
    private double val;
    
    public NamedConstant(String name, Double val){
        this.name = name;
        if(Constants.namedConstants.containsKey(name)){
            this.val = Constants.namedConstants.get(name);
        }
        else{
            throw new IllegalExpressionException("illegal");
        }
    }

    public Boolean isNamedConstant(){
        return true;
    }

    public double getValue(){
        return this.val;
    }

    public String toString() {
        return this.name;
    }

    public boolean equals(Object other) {
        if (other instanceof Constants) {
            return this.equals((Constants) other);
        } else {
            return false;
        }
    }

    public boolean equals(Constants other) {
        return this.val == other.val;
    }

    public SymbolicExpression eval(Environment vars){
        return new Constant(val);
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
        return null;
    }
}
    
