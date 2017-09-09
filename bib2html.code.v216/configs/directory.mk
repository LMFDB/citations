directory:
	@if [ ! -d $(B2H_DIR_OBJ) ] ;\
	then \
		echo "*" ; \
		echo "* Creation of the $(B2H_DIR_OBJ) directory..." ; \
		echo "*" ; \
		mkdir $(B2H_DIR_OBJ) ; \
	fi ;
	@if [ ! -d $(B2H_OBJ_PATH) ] ;\
	then \
		echo "*" ; \
		echo "* Creation of the $(B2H_OBJ_PATH) directory..." ; \
		echo "*" ; \
		mkdir $(B2H_OBJ_PATH) ; \
	fi ;

