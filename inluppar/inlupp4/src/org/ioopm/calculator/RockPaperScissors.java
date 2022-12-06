package org.ioopm.calculator;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class RockPaperScissors {

    public static void main(String [] args){
        String filename = "strategy.input";
        try (Scanner sc = new Scanner(new File(filename))){

            while(sc.hasNext()) {
                String character = sc.next();
                System.out.println(character);
                character = sc.next();
                System.out.println(character);
                    
            }
        
        }catch (FileNotFoundException ex){
            System.out.println("hej");
        }
    }


enum Result{
    WIN, LOSE, DRAW;
}

abstract class Shape{
    abstract public Result play(Shape shape);
    abstract public int getScore();
}

class Rock extends Shape{
    @Override 
    public int getScore(){
        return 1;
    }

    @Override
    public Result play(Shape shape){
        return Result.WIN;
    }
}



}
