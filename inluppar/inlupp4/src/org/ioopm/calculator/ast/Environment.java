package org.ioopm.calculator.ast;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;

public class Environment extends HashMap<Variable, SymbolicExpression> {

    public void print() {
        Set<Variable> keys = this.keySet();

        for (Variable v : keys){
            String key = v.toString();
            String value = this.get(v).toString();
            System.out.println(key  + " = " + value);
        }
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: ");
        TreeSet<Variable> vars = new TreeSet<>(this.keySet());
        for (Variable v : vars) {
            sb.append(v.getName());
            sb.append(" = ");
            sb.append(this.get(v));
            sb.append(", ");
        }
        return sb.toString();
    }
}