package org.ioopm.calculator.ast;

public class EvaluationVisitor implements Visitor {
    private Environment env = null;

    public SymbolicExpression evaluate(SymbolicExpression topLevel, Environment env) {
        this.env = env;
        return topLevel.accept(this);
    }

    // This method gets called from Addition.accept(Visitor v) -- you should
    // be able to see from the eval() methods how these should behave (i.e., 
    // compare this method with your Addition::eval() and Symbolic.addition) 
    public SymbolicExpression visit(Addition n) {
        // Visit the left hand side and right hand side subexpressions
        SymbolicExpression left = n.lhs.accept(this);
        SymbolicExpression right = n.rhs.accept(this);
        // When we come back here, the visitor has visited all subexpressions, 
        // meaning left and right point to newly created trees reduced to 
        // the extent possible (best case -- both are constants)

        // If subexpressions are fully evaluated, replace them in
        // the tree with a constant whose value is the sub of the
        // subexpressions, if not, simply construct a new addition
        // node from the new subexpressions
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        } else {
            return new Addition(left, right);
        }
    }

    public SymbolicExpression visit(Vars n){
        return n;
    }

    public SymbolicExpression visit(Subtraction n){
        SymbolicExpression argl = n.lhs.accept(this);
        SymbolicExpression argr = n.rhs.accept(this);
    
        if (argl.isConstant() && argr.isConstant()) {
                double sub = argl.getValue() - argr.getValue();
                return new Constant(sub);
            } 
            return new Subtraction(argl, argr);
        }

    public SymbolicExpression visit(Variable n){
        if (this.env.containsKey(n)) {
            return env.get(n);
        } else {
            return new Variable(n.toString());
        }
    }

    public SymbolicExpression visit(Sin n){
        SymbolicExpression arg = n.arg.accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }

    public SymbolicExpression visit(Constant n){
        return new Constant (n.getValue());
    }

    public SymbolicExpression visit(Cos n)
    {
    SymbolicExpression arg = n.arg.accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }
    
    public SymbolicExpression visit(Quit n){
        return n;
    }

    public SymbolicExpression visit(Log n){
        SymbolicExpression arg = n.arg.accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }

    public SymbolicExpression visit(Exp n){
        SymbolicExpression arg = n.arg.accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }

    public SymbolicExpression visit(Negation n){
        SymbolicExpression arg = n.arg.accept(this);
        if (arg.isConstant()) {
            return new Constant((-1) * (arg.getValue()));
        } else {
            return new Negation(arg);
        }
    }

    public SymbolicExpression visit(Multiplication n){
        SymbolicExpression argl = n.lhs.accept(this);
        SymbolicExpression argr = n.rhs.accept(this);

        if (argl.isConstant() && argr.isConstant()) {
                double mult = argl.getValue() * argr.getValue();
                return new Constant(mult);
            } 
            return new Multiplication(argl, argr);
    }

    public SymbolicExpression visit(Division n){
        SymbolicExpression argl = n.lhs.accept(this);
        SymbolicExpression argr = n.rhs.accept(this);
        
        if(argr.getValue() == 0){
            throw new IllegalExpressionException("illegal divition with zero");
        }
        else if (argl.isConstant() && argr.isConstant()) {
                double divide = argl.getValue() / argr.getValue();
                return new Constant(divide);
            } 
            return new Division(argl, argr);
    }
    
    public SymbolicExpression visit(Assignment n){
        SymbolicExpression argl = n.lhs.accept(this);
        SymbolicExpression argr = n.rhs.accept(this);
      
        if (Constants.namedConstants.containsKey(n.rhs.toString()))
        {
            throw new IllegalExpressionException("Error: cannot redefine a named constant.");
        }
        else if (env.containsKey(n.rhs))
        {
            throw new IllegalExpressionException("Error: cannot redefine an already assigned variable.");
        }
        else if (argr instanceof Variable){
            
            env.put((Variable)(argr), argl);

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

    public SymbolicExpression visit(Clear n) {
         env.clear();
         return n;
    }

}
    