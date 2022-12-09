package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class CosTest {
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    Constant con = new Constant(5);
    Cos cos = new Cos(con);

    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        assertTrue(5 == cos.getValue());
    }

    @Test
    public void isConstantTest(){
        assertFalse(cos.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("cos", cos.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(cos.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(0 == cos.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("cos 5.0", cos.toString());
    }

    @Test
    public void equalsTest(){
        Cos cos2 = new Cos(con);
        assertTrue(cos2.equals(cos));
    }

    @Test
    public void evaluateTest(){
        assertEquals(new Constant(Math.cos(5)), evaluator.evaluate(cos, env));
    }


}