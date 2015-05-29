all:
	astyle --style=java --indent=tab *.java
	rm -f *.class
	javac *.java
	gcj -o Master --main=Main *.java
