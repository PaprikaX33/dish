#ifndef IDSH_VERSION_STRING_TEXT_HEAD_H
#define IDSH_VERSION_STRING_TEXT_HEAD_H

#define STRINGIFY(str) #str
#define EXPAND_STRING(str) STRINGIFY(str)

static char const * versionString =
  "idsh " EXPAND_STRING(VERSION_MAJOR) "." EXPAND_STRING(VERSION_MINOR) "." EXPAND_STRING(VERSION_PATCH) "\n"
  "Copyright (C) 2020 X33\n"
  "Licensed under MIT License\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.\n";


static char const * usageString = "Usage: idsh [options]";

static char const * optionString =
  "Options are:\n"
  " -? --help    Show this messages and exits\n"
  " -V --version Show program version and License and exits";

#undef STRINGIFY
#undef EXPAND_STRING

/* Local Variables: */
/* mode: c */
/* End: */
#endif //IDSH_VERSION_STRING_TEXT_HEAD_H
