package org.ioopm.calculator.ast;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;
import java.util.Stack;

public class Environment extends Stack<HashMap<Variable, SymbolicExpression>> {
    protected Stack<HashMap<Variable, SymbolicExpression>> stack = new Stack<>();

    public Environment(){
        HashMap<Variable, SymbolicExpression> hash = new HashMap<Variable, SymbolicExpression>();
        this.stack.push(hash);
    }
    /* 
    public void print() {
        Set<Variable> keys = this.keySet();

        for (Variable v : keys){
            String key = v.toString();
            String value = this.get(v).toString();
            System.out.println(key  + " = " + value);
        }
    }
    */

    @Override
    public String toString(){
        Stack<HashMap<Variable, SymbolicExpression>> temp_stack = (Stack<HashMap<Variable, SymbolicExpression>>) this.stack.clone();
        HashMap<Variable, SymbolicExpression> temp = temp_stack.pop();
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: ");
        TreeSet<Variable> vars = new TreeSet<>(temp.keySet());
        for (Variable v : vars) {
            sb.append(v.getName());
            sb.append(" = ");
            sb.append(temp.get(v));
            sb.append(", ");
        }
        return sb.toString();
    }

    public SymbolicExpression get(Variable v){
        Stack<HashMap<Variable, SymbolicExpression>> temp_stack = (Stack<HashMap<Variable, SymbolicExpression>>) this.stack.clone();
        HashMap<Variable, SymbolicExpression> temp = temp_stack.pop();    
        System.out.println("get " + temp.get(v));
        return temp.get(v);
        /*
        for(int i = 0; i < this.stack.size(); i++){
            HashMap<Variable, SymbolicExpression> temp_ht = temp_stack.pop();    
            if(temp_ht.containsKey(v)){
                return temp_ht.get(v);
            }
        }
        return v;
        */
    }

    public void put(Variable v, SymbolicExpression e){
        HashMap<Variable, SymbolicExpression> temp_hash = this.stack.pop();
        temp_hash.put(v,e);
        System.out.println("put " + temp_hash.put(v,e));
        this.stack.push(temp_hash);
    }

    public Boolean containsKey(SymbolicExpression key){
        Stack<HashMap<Variable, SymbolicExpression>> temp_stack = (Stack<HashMap<Variable, SymbolicExpression>>) this.stack.clone();
        HashMap<Variable, SymbolicExpression> temp_ht = temp_stack.pop();    
        return temp_ht.containsKey(key);
      /*  for(int i = 0; i < this.stack.size(); i++){
            HashMap<Variable, SymbolicExpression> temp_ht = temp_stack.pop();    
            if(temp_ht.containsKey(key)){
                temp_stack.push(temp_ht)
                return true;
            }
        }
        return false;
        */
    }

    public void push(){
        HashMap<Variable, SymbolicExpression> temp_ht = new HashMap<>();
        this.stack.push(temp_ht);
    }

    public HashMap<Variable, SymbolicExpression> pop(){
        return this.stack.pop();
    }
}