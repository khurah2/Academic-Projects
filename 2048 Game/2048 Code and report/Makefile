ifeq ($(OS),Windows_NT)
	SEP=;
else
	SEP=:
endif

JFLAGS = -g
JCLASS = -cp "src$(SEP).$(SEP)../junit-4.5.jar"
JC = javac
JVM = java

.PHONY: test doc 

test:
	find . -name '*.class' -exec rm -f {} \;
	$(JC) $(JCLASS) $(JFLAGS) src/AllTests.java
	$(JVM) $(JCLASS) org.junit.runner.JUnitCore AllTests

doc:
	doxygen doxConfig
	cd latex && $(MAKE)

run:
	$(JC) $(JCLASS) $(JFLAGS) src/Main.java
	$(JVM) $(JCLASS) Main

clean:
	rm -rf html
	rm -rf latex
	cd src
	rm **/*.class

