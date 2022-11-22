package org.ioopm.calculator.ast;

public class NamedConstant extends Constant{
    
    public static Double value(String name){
        if(Constants.namedConstants.containsKey(name)){
            return Constants.namedConstants.get(name);
        }
        else{
            throw new IllegalExpressionException("illegal");
        }
    }

    public Boolean isNamedConstant(){
        return true;
    }

    public NamedConstant(String str, Double val) {
        super(value(str));
    }
}
    
