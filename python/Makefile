PYTHON=python3
MAIN=$(PROGRAM).py
FILES=driver.py
PROGRAM=calculator

# compile all python files
all:
	$(PYTHON) $(MAIN)

# run main program
run: 
	$(PYTHON) $(MAIN)

# run pycodestyle
get_style:
	@ pycodestyle $(MAIN) ||:

# run tests
test:
	$(PYTHON) -m unittest discover -s 

# mypy file name
mypy:
	mypy ./driver.py
	
# auto pep 8
fix_style:
	@autopep8 --in-place --aggressive $(MAIN) ||: 


# install dependencies
install:
	pip install -r requirements.txt

uml:
	pyreverse -o png .
	open classes.png

# retrieve server host ip address
ip:
	
# create server
server: 
	hostname -i
	python3 -m http.server 8000

# create virtual environment
venv:
	python -m venv venv
	source venv/bin/activate
	pip install -r requirements.txt

# clean up
clean:
	rm -rf venv

