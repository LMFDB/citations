# For testing use "make" and test that the file citations.html looks
# good.

# For use in the LMFDB use "make plain" and copy the files
# citations_content.html and citations_content_bib.html to
# lmfdb/templates/

all: citations.bib
	bibtex2html -a -t "Citations for the LMFDB" -header "" -footer "" -nofooter -f url -html-entities citations.bib

plain: citations.bib
	bibtex2html -a -nodoc -header "" -footer "" -nofooter -f url -html-entities -o citations_content citations.bib
	sed -i 's!citations_content\.html!/citation/citations!g' citations_content_bib.html
	sed -i 's!citations_content_bib\.html!/citation/citations_bib!g' citations_content.html

# -d for sort by Date instead of alphabetical
# -a for sort Alphabetically by author
# -f url adds a web link for any entries with a url field
# -nodoc produces only the <body> part for inclusion into another html file

