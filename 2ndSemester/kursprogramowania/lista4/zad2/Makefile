all: build run

build:
	javac --module-path /home/michal/vsprojects/pwr/2ndSemester/kursprogramowania/lista4/javafx_modules --add-modules javafx.controls App.java

run: 
	java --module-path /home/michal/vsprojects/pwr/2ndSemester/kursprogramowania/lista4/javafx_modules --add-modules javafx.controls App

clean:
	rm -rf *.class
	rm log.txt