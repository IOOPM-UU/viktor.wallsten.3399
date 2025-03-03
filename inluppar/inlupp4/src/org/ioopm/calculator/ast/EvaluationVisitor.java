package org.ioopm.calculator.ast;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;
import java.util.function.Function;
import java.util.Stack;

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

        public SymbolicExpression visit(Variable n) {
            if (this.env.containsKey(n)) {
                return env.get(n);
            } else if (Constants.namedConstants.containsKey(n.toString())) {
                return new Constant(Constants.namedConstants.get(n.toString()));
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
        SymbolicExpression argr = n.rhs;
      
        if (Constants.namedConstants.containsKey(n.rhs.toString()))
        {
            throw new IllegalExpressionException("Error: cannot redefine a named constant.");
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

    public SymbolicExpression visit(Scope n){
       this.env.push();
       SymbolicExpression arg = n.arg.accept(this);
       this.env.pop();
       return arg;
    }

    public SymbolicExpression visit (GreaterthanEquals n){
        if (n.lhs.accept(this).getValue() >= n.rhs.accept(this).getValue()){
            return new SysBool(true);
        }
        return new SysBool(false);     
    }
    public SymbolicExpression visit(Eq n){
        if (n.lhs.accept(this).getValue() == n.rhs.accept(this).getValue()){
            return new SysBool(true);
        }
        return new SysBool(false);  
    }

    public SymbolicExpression visit(Lessthanequals n){
        if (n.lhs.accept(this).getValue() <= n.rhs.accept(this).getValue()){
            return new SysBool(true);
        }
        return new SysBool(false);     
    }
    

    public SymbolicExpression visit(Lessthan n){
        if (n.lhs.accept(this).getValue() < n.rhs.accept(this).getValue()){
            return new SysBool(true);
        }
        return new SysBool(false);     
    }
    
    
    public SymbolicExpression visit(Greaterthan n){
        if (n.lhs.accept(this).getValue() > n.rhs.accept(this).getValue()){
            return new SysBool(true);
        }
        return new SysBool(false);     
    }

    public SymbolicExpression visit(Conditonal n){
        if(n.arg.accept(this).getBool()){
            return n.s1.accept(this);
        }
        return n.s2.accept(this);
    }

    public SymbolicExpression visit(SysBool n){
        return n;
    }

    public SymbolicExpression visit(Sequence n){
        SymbolicExpression result = null;

        for (SymbolicExpression r : n.list) {
            result = r.accept(this);
        }
 
        return result;
    }

    public SymbolicExpression visit(FunctionDeclaration n){
        return n;
    }


    public SymbolicExpression visit(FunctionCall n){
        for (int i = 0; i < n.list.size(); i++){
            env.put(n.funcDec.parameters.get(i), n.list.get(i).accept(this));
        }
        SymbolicExpression result = n.funcDec.body.accept(this);  
        return result;
       
    }


}
    