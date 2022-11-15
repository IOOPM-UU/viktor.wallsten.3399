package org.ioopm.calculator.ast;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class Environment extends HashMap<Variable, SymbolicExpression> {

    public void print() {
        Set<Variable> keys = this.keySet();

        for (Variable v : keys){
            String key = v.toString();
            String value = this.get(v).toString();
            System.out.println(key  + " = " + value);
        }
    }
}