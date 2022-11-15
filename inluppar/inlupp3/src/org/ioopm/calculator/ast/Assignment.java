package org.ioopm.calculator.ast;

public class Assignment extends Binary{

    public Assignment (SymbolicExpression rhs, SymbolicExpression lhs){
        super(rhs, lhs);
    }

    public String getName() {
        return "=";
    }

    public String toString(){
        return this.getName();
    }

    public SymbolicExpression eval(Environment vars){
        SymbolicExpression argl = this.lhs.eval(vars);
        SymbolicExpression argr = this.rhs.eval(vars);
      
        if (Constants.namedConstants.containsKey(this.rhs.toString()))
        {
            throw new IllegalExpressionException("Error: cannot redefine a named constant.");
        }
        else if (vars.containsKey(this.rhs))
        {
            throw new IllegalExpressionException("Error: cannot redefine an already assigned variable.");
        }
        else if (argr instanceof Variable){
            
            vars.put((Variable)(argr), argl);

            if (argl.isConstant()){
                return new Constant(argl.getValue());
            }
            else
            {
                return argl;
            }
        }
        else
        {
            throw new IllegalExpressionException("Error: cannot assign to a non-variable");
        }
    }
}