all:
	rm -f *.class
	astyle --style=java --indent=tab *.java || echo ""
	rm -f *.class
	javac *.java
	gcj -o Master --main=Main *.java
