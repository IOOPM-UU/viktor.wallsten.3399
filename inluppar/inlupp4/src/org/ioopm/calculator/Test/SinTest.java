package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class SinTest {
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    Constant con = new Constant(5);
    Sin sin = new Sin(con);

    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        assertTrue(5 == sin.getValue());
    }

    @Test
    public void isConstantTest(){
        assertFalse(sin.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("sin", sin.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(sin.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(0 == sin.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("sin 5.0", sin.toString());
    }

    @Test
    public void equalsTest(){
        Sin sin2 = new Sin(con);
        assertTrue(sin2.equals(sin));
    }

    @Test
    public void evaluateTest(){
        assertEquals(new Constant(Math.sin(5)), evaluator.evaluate(sin, env));
    }


}