package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class LogTest {
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    Constant con = new Constant(5);
    Log log = new Log(con);

    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        assertTrue(5 == log.getValue());
    }

    @Test
    public void isConstantTest(){
        assertFalse(log.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("log", log.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(log.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(0 == log.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("log 5.0", log.toString());
    }

    @Test
    public void equalsTest(){
        Log log2 = new Log(con);
        assertTrue(log2.equals(log));
    }

    @Test
    public void evaluateTest(){
        assertEquals(new Constant(Math.log(5)), evaluator.evaluate(log, env));
    }


}