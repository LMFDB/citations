#ifndef __CEntry_h_
#define __CEntry_h_

#include <string>
#include <field/CField.h>
#include <field/CFieldString.h>
#include <field/CFieldName.h>
#include <field/CFieldInteger.h>
#include <field/CFieldBooleen.h>
#include <field/CFieldMonth.h>
#include <field/CFieldPages.h>
#include <field/CFieldKeyword.h>
#include <field/CFieldCrossref.h>
#include <field/CFieldYesNo.h>
#include <config/CConfig.h>

#define APPLY "does not apply here" <<endl

class CEntry
{

 protected:
  CConfig *cnf ;
 public:
  int type_of_entry  ;
  string key ;
  string s_entry ;
  string s_entry_with_no_space ;
 public:

  void GetKey(string &s) ;
  void PrintKey() ;
  void Init() ;
  CEntry() {;}
  virtual void kill() { ; }   
  virtual ~CEntry() {;}
  CEntry(int _type_of_entry, string &s, CConfig *cnf) ;

  void PrintEntryType()  ;

  string CreateBibtex() ;
  string CreateEE() ;
  int CreateHtml(string &s)  ;
  void Print(string &s);
  void PrintEE(string &s);
  void PrintHTML(string &s);
  void PrintBIBTEX(string &s);
  void PrintLATEX(string &s);

  int ExtractFields(string &s) ;
  int ReadNextField(string &s) ;

  int Contact(string &s) ;
  void CreatePublicationPage(ofstream &f) ;
  void CreatePublicationPageFrench(ofstream &f) ;

  CFieldAuthor *f_author ;
  CFieldEditor   *f_editor ;

  CFieldTitle *f_title ;
  CFieldURL *f_url;
  CFieldArxiv *f_arxiv;
  CFieldDOI *f_doi;
  CFieldURLtransp *f_urltransp ;
  CFieldURLinterne *f_urlinterne ;
  CFieldAbstract *f_abstract ;
  CFieldAddress   *f_address ;
  CFieldAddresse   *f_addresse ;
  CFieldJournal  *f_journal ;
  CFieldBookTitle  *f_booktitle ;

  CFieldPublisher *f_publisher ;
  CFieldHowpublished *f_howpublish ;
  CFieldSeries *f_series ;
  CFieldSchool *f_school ;
  CFieldInstitution *f_institution ;

  // integer
  CFieldVolume *f_volume ;
  CFieldChapter *f_chapter  ;
  CFieldYear *f_year ;
  CFieldNumber *f_number ;

  CFieldWorkshop *f_workshop ;
  CFieldRA *f_ra ;
  CFieldToAppear *f_toappear ;
  CFieldConfnat *f_confnat ;
  CFieldType *f_type ;
  CFieldNote *f_note ;
  CFieldHDR *f_hdr ;

  // New field required by INRIA
  CFieldXInvitedConference *f_xinvitedconference ;
  CFieldXScientificPopularization *f_xscientificpopularization ;
  CFieldXInternationalAudience  *f_xinternationalaudiance ;
  CFieldXEditorialBoard *f_xeditorialboard ;
  CFieldXProceedings *f_xproceedings;
  CFieldXNote *f_xnote;
  CFieldXMisc *f_xmisc;

  // pages
  CFieldPages *f_pages ;
  // month
  CFieldMonth *f_month ;
  CFieldKeyword *f_keyword ;
  CFieldCrossref *f_crossref ;
  int Download(string &url, string &s) ;
  int DownloadArxiv(string &url, string &s) ;
  int DownloadIcon(string &url, string &s) ;
  int Compressed(string &url, string &s) ;
  int CheckKeyword(CConfig *cnf) ;
} ;

#endif

