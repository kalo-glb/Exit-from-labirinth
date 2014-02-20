ARDUINOLIBS = /home/kalo/sketchbook/libraries

getLibs:
	rm -r -f ./libs;
	cp -R $(ARDUINOLIBS) ./libs

commit: getLibs
	git commit -m $(MESSAGE)
    
push:
	git push -u origin master
    
setLibs:
	rm -r -f $(ARDUINOLIBS)
	cp -R ./libs $(ARDUINOLIBS)

