all_ast:
	javac -d classes -sourcepath src src/org/ioopm/calculator/parser/*.java
	javac -d classes -sourcepath src src/org/ioopm/calculator/ast/*.java

test_p:
	javac  -d classes -sourcepath src src/org/ioopm/calculator/parser/test.java
	java -ea -cp classes org.ioopm.calculator.parser.test


all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

run: all
	java -cp classes org.ioopm.calculator/Calculator

clean:
	rm -rf classes

test:
	javac -cp junit-platform-console-standalone-1.8.1.jar:classes src/org/ioopm/calculator/AdditionTest.java

runTest: test
	java -jar junit-platform-console-standalone-1.8.1.jar -cp . -c org.ioopm.calculator/AdditionTest