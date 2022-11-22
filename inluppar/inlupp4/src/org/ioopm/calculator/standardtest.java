package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;

import org.junit.Test;

public class standardtest {

    @Test
    public void testTrue(){
        assertTrue(true);
    }
    
    @Test
    public void testFalse(){
        assertFalse(false);
    }

}