all: citations.bib
	bibtex2html -a -t "Citations for the LMFDB" -header "" -footer "" -nofooter -f url -html-entities citations.bib

# -d for sort by date instead of alphabetical
