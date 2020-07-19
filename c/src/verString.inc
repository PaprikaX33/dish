#ifndef IDSH_VERSION_STRING_TEXT_HEAD_HPP
#define IDSH_VERSION_STRING_TEXT_HEAD_HPP

#define STRINGIFY(str) #str
#define EXPAND_STRING(str) STRINGIFY(str)

static char const * VersionString = "idsh "
  EXPAND_STRING(VERSION_MAJOR) "." EXPAND_STRING(VERSION_MINOR) "." EXPAND_STRING(VERSION_PATCH) "\n"
  "Copyright (C) 2020 X33\n"
  "Licensed under MIT License\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.\n";

#undef STRINGIFY
#undef EXPAND_STRING

#endif //IDSH_VERSION_STRING_TEXT_HEAD_HPP

/* Local Variables: */
/* mode: c */
/* End: */
