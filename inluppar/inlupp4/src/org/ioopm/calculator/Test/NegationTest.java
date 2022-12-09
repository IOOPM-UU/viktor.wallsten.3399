package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class NegationTest {
    Negation neg = new Negation(new Constant(5));
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();


    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        assertTrue(5 == neg.getValue());
    }

    @Test 
    public void isConstantTest(){
        assertFalse(neg.isConstant());
    }   

    @Test
    public void getNameTest(){
        assertEquals("-", neg.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(neg.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(0 == neg.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("- 5.0", neg.toString());
    }

    @Test
    public void equalsTest(){
        Negation neg2 = new Negation(new Constant(5));
        assertTrue(neg2.equals(neg2));
    }

    @Test
    public void evaluateTest(){
        assertEquals(new Constant(-5), evaluator.evaluate(neg, env));
    }

}
