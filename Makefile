# For testing either use "make full" and test that the file
# citations.html looks good, or "make lmfdb" and look at
# citations_content.html.

# For use in the LMFDB use "make lmfdb" and copy the files
# citations_content.html and citations_content_bib.html to
# lmfdb/templates/ then update the date in the file
# lmfdb/templates/citations_update.html .

lmfdb: citations.bib
	bibtex2html -a -nodoc -header "" -footer "" -nofooter -f url -html-entities -o citations_content citations.bib
	sed -i 's!citations_content\.html!/citation/citations!g' citations_content_bib.html
	sed -i -e 's/{{/{ {/g' citations_content_bib.html
	sed -i -e 's/}}/} }/g' citations_content_bib.html
	sed -i 's!citations_content_bib\.html!/citation/citations_bib!g' citations_content.html

# -d for sort by Date instead of alphabetical
# -a for sort Alphabetically by author
# -f url adds a web link for any entries with a url field
# -nodoc produces only the <body> part for inclusion into another html file

# The next target includes head and footer and might be easier to proofread.

full: citations.bib
	bibtex2html -a -t "Citations for the LMFDB" -header "" -footer "" -nofooter -f url -html-entities citations.bib

