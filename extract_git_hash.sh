#!/bin/bash

# SVN Revision Extractor for Unix systems
# Written by Burlex, 2008/02/20
# Rewritten by Twl, 2010/05/10
# Updated 2010/06/12

git log | grep commit | cut -f2 -d' ' > lg
sed '/^$/d' lg > hashes
rm -f lg

hash=`read -r hd < hashes && echo $hd`
rev=`wc hashes | sed -e 's/^[ \t]*//' | cut -f1 -d' '`
rm -f hashes

echo "// This file was automatically generated by the GIT revision extractor." > git_revision.h
echo "// There is no need to modify it." >> git_revision.h
echo "" >> git_revision.h
echo "#ifndef GIT_REVISION_H" >> git_revision.h
echo "#define GIT_REVISION_H" >> git_revision.h
echo "" >> git_revision.h
echo "static const char * BUILD_TAG = \"ASCNHALF-0.1\";" >> git_revision.h
echo "static const char * BUILD_HASH = \""$hash"\";" >> git_revision.h
echo "static int BUILD_REVISION = $rev;" >> git_revision.h
echo "static const char * BUILD_USER = \"$USER\";" >> git_revision.h
echo "static const char * BUILD_HOST = \"`hostname`\";" >> git_revision.h
echo "" >> git_revision.h
echo "#endif         // GIT_REVISION_H" >> git_revision.h
echo "" >> git_revision.h
mv ./git_revision.h ./src/ascnhalf-shared
echo $hash;
