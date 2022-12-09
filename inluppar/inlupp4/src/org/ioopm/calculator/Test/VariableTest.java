package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class VariableTest {
    Variable var1 = new Variable("x");
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        assertEquals("x", var1.getValue());
    }

    @Test
    public void isConstantTest(){
        assertFalse(var1.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("x", var1.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(var1.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(200 == var1.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("x", var1.toString());
    }

    @Test
    public void equalsTest(){
        Variable var2 = new Variable("x");
        assertTrue(var1.equals(var2));
    }

    @Test
    public void evaluateTest(){
        env.put(var1, new Constant(5));
        assertEquals(new Constant(5), evaluator.evaluate(var1, env));
    }

}