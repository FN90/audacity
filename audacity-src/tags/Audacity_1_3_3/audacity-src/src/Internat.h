/**********************************************************************

  Audacity: A Digital Audio Editor

  Internat.h

  Markus Meyer
  Dominic Mazzoni (Mac OS X code)

**********************************************************************/

#ifndef __AUDACITY_INTERNAT__
#define __AUDACITY_INTERNAT__

#include <wx/string.h>
#include <wx/longlong.h>

class Internat
{
public:
   static void CleanUp();

   // Initialize internationalisation support. Call this once at
   // program start.
   static void Init();

   // Get the decimal separator for the current locale. Normally, this is
   // a decimal point ('.'), but e.g. Germany uses a comma (',').
   static wxChar GetDecimalSeparator();

   // Convert a string to a number. This function will accept BOTH point
   // and comma as a decimal separator, regardless of the current locale.
   // Returns 'true' on success, and 'false' if an error occurs.
   static bool CompatibleToDouble(const wxString& stringToConvert, double* result);

   // Function version of above.
   static double CompatibleToDouble(const wxString& stringToConvert);

   // Convert a number to a string, always uses the dot as decimal separator
   static wxString ToString(double numberToConvert,
                     int digitsAfterDecimalPoint = -1);

   // Convert a number to a string, uses the user's locale's decimal separator
   static wxString ToDisplayString(double numberToConvert,
                     int digitsAfterDecimalPoint = -1);

   // Convert a number to a string while formatting it byte, KB, MB, GB
   static wxString FormatSize(wxLongLong size);
   static wxString FormatSize(double size);

   // Convert strings to and from UTF-8 (used for XML files).
   static wxString UTF8ToLocal(const wxString &s);
   static wxString LocalToUTF8(const wxString &s);

   static wxString ToFilename(const wxString &s);
   static wxString FromFilename(const wxString &s);

   // Utility function - takes a translatable string to be used as a
   // menu item, for example _("&Splash...\tAlt+S"), and strips all of the
   // menu accelerator stuff from it, to make "Splash".  That way the
   // same translatable string can be used both when accelerators
   // are needed and when they aren't, saving translators effort.
   static wxString StripAccelerators(const wxString& str);

private:
   static wxChar mDecimalSeparator;
   static wxMBConv *mConvLocal;

   #ifdef __WXMAC__
   static void *mTECToUTF;
   static void *mTECFromUTF;
   #endif
};

#define _NoAcc(X) Internat::StripAccelerators(_(X))

// Use this macro to wrap all filenames and pathnames that get
// passed directly to a system call, like opening a file, creating
// a directory, checking to see that a file exists, etc...
#if defined(__WXMAC__)
#define OSFILENAME(X) ((char *) (const char *)(X).fn_str())
#else
#define OSFILENAME(X) ((char *) (const char *)(X).mb_str())
#endif

// Convert C strings to wxString
#define UTF8CTOWX(X) wxString((X), wxConvUTF8)
#define LAT1CTOWX(X) wxString((X), wxConvISO8859_1)

#endif

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: 14ff0c8a-5ad9-46e2-8162-76f9e9382186

