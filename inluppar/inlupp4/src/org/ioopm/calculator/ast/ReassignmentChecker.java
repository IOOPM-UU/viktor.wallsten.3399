package org.ioopm.calculator.ast;

import java.util.HashMap;

public class ReassignmentChecker {
    Environment environment = null;
    HashMap<Variable, SymbolicExpression> l_e = null;

    public ReassignmentChecker(Environment e){
        this.environment = e;
        this.l_e = new HashMap<Variable, SymbolicExpression>();
    }

    
}
