========================================================================
    STATIC LIBRARY : Library Project Overview
========================================================================

AppWizard has created this Library library project for you.

No source files were created as part of your project.


Library.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Library.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

/////////////////////////////////////////////////////////////////////////////
Other notes:

Our project uses a boosted tokenizer and a boosted map. To use this library, you need to first download
the C++ boost library, and then go to the library project's properties, and under C++ click on general->include->additional include directories.
You then need to make that the path to the boost library, wherever you had downloaded/placed it. As of now, it has our path in it
and the library will not work if you do not change this.

/////////////////////////////////////////////////////////////////////////////
