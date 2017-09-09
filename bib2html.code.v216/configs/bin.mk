
# Rule for combining compilation and dependency generation
# - put binaries in current directory
%$(SUFFIX).exe : %.cpp $(B2H_LIBNAME)
	@echo "*"
	@echo "* Create the binary file $@ for $< "
	@echo "*"
	$(CXXALL)  -o $@ $< $(LDFLAGS) $(LIBS)
	cp $@ $(B2H_DIR_BIN)/.
