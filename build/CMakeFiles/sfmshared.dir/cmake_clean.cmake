FILE(REMOVE_RECURSE
  "../lib/libsfm.pdb"
  "../lib/libsfm.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/sfmshared.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
