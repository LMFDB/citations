OBJECTS_TMP =$(SOURCES:%.cpp=$(B2H_OBJ_PATH)/%.o)
OBJECTS     =$(OBJECTS_TMP:.c=.o)



$(LIB) : $(OBJECTS)
	$(AR) $@ $(B2H_OBJ_PATH)/*.o


# Rule for combining compilation and dependency generation:
# - put objects in $(B2H_OBJ_PATH)

$(B2H_OBJ_PATH)/%.o : %.cpp
	@echo "*"
	@echo "* Build $@ from $<  "
	@echo "*"
	$(CXXALL)  -o $@ -c $<


$(B2H_OBJ_PATH)/%.o : %.c
	@echo "*"
	@echo "* Build $@ from $<  "
	@echo "*"
	$(CXXALL)  -o $@ -c $<

