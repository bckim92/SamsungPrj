FILE(REMOVE_RECURSE
  "../lib/libsfm.pdb"
  "../lib/libsfm.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/sfmstatic.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
