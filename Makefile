#
# Makefile for a CS 370 lab or programming assignment.
# Do not modify this file!!!
#

SUBMIT_URL = https://cs.ycp.edu/marmoset/bluej/SubmitProjectViaBlueJSubmitter
COURSE_NAME = CS 370
SEMESTER = Fall 2020
PROJECT_NUMBER = assign01

all :
	@echo "Please type 'make submit' to submit this project"

submit : clean submit.properties solution.zip
	./submitToMarmoset.pl solution.zip submit.properties

solution.zip : collected-files.txt
	@echo "Creating a solution zip file"
	@zip -9 $@ `cat collected-files.txt`
	@rm -f collected-files.txt

# Create the submit.properties file that describes how
# the project should be uploaded to the Marmoset server.
submit.properties : nonexistent
	@echo "Creating submit.properties file"
	@rm -f $@
	@echo "submitURL = $(SUBMIT_URL)" >> $@
	@echo "courseName = $(COURSE_NAME)" >> $@
	@echo "semester = $(SEMESTER)" >> $@
	@echo "projectNumber = $(PROJECT_NUMBER)" >> $@

# Collect the names of all files that don't appear
# to be generated files.
collected-files.txt :
	@echo "Collecting the names of files to be submitted"
	@rm -f $@
	@find . \( \
				-maxdepth 3 -name '*\.cpp' \
				-or -name '*\.h' \
				-or -name 'CMakeLists.txt' \
				-or -name '*\.vert' \
				-or -name '*\.frag' \
				-or -name '*\.dylib' \
				-or -name '*\.a' \
				-or -name '*\.dll' \
				-or -name '*\.lib' \
				-or -name '*\.jpg' \
				-or -name '*\.png' \
			\) -print \
		| perl -ne 's,\./,,; print' \
		> $@

# This is just a dummy target to force other targets
# to always be out of date.
nonexistent :

# Remove generated files.
clean : 
	rm -f collected-files.txt submit.properties solution.zip