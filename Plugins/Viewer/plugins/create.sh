if [ $# != 2 ]; then 
  echo -e "usage: ./create.sh origin destination" 
  exit 1
fi
rm -r -f $2
mkdir $2
cp $1*.cpp $2/$2.cpp
cp $1*.h $2/$2.h
echo "SUBDIRS += $2" >> plugins.pro
echo "TARGET     = \$\$qtLibraryTarget($2)  # Nom del plugin " > $2/$2.pro
echo "include(../common.pro)" >> $2/$2.pro
echo "QMAKE_CXXFLAGS += -std=c++11" >> $2/$2.pro
