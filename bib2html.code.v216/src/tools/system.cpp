#include <tools/system.h>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
/**************************************************
 *
 * directory management
 *
 Les 2 fonctions suivantes ont ete ecrites par G. Maladin
 dans bibtex2html
 **************************************************/

int check_directory(const  char *dir )
{
  char *proc = "check_directory";
  struct stat stbuf;

  if ( dir == NULL || dir[0] == '\0' ) {
    printf( "%s: invalid directory name\n", proc );
    return( -1 );
  }
  if ( stat( dir, &stbuf ) != 0 ) {
    printf( "%s: can't stat directory '%s' (doesn't exist?)\n",
	    proc, dir );
    return( -2 );
  }
  if ( (stbuf.st_mode & S_IFDIR) == 0 ) {
    printf( "%s: '%s' is not a directory\n", proc, dir );
    return( -3 );
  }
  if ( (stbuf.st_mode & S_IWUSR) == 0 ) {
    printf( "%s: '%s' is not writable\n", proc, dir );
    return( -4 );
  }
  return( 1 );
}

int make_directory(const  char *dir )
{
  char *proc = "make_directory";
  struct stat stbuf;

  if ( dir == NULL || dir[0] == '\0' ) {
      printf( "%s: invalid directory name\n", proc );
    return( -5 );
  }
  if ( stat( dir, &stbuf ) != 0 ) {
    if ( mkdir( dir, (mode_t)0755 ) != 0 ) {
      printf("%s: unable to create directory '%s'\n", proc, dir );
      return( -6 );
    }
    printf("%s: has created directory '%s'\n", proc, dir );
  }
  return( check_directory( dir ) );
}
