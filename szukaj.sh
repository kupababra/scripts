#!/bin/bash

# Skrypt do wyszukiwania pakietów w Gentoo
# id3fix@retro-technology.pl

if [ -z "$1" ]; then
  echo "Podaj nazwę pakietu do wyszukania."
  exit 1
fi

# Zmienna z nazwą pakietu
PACKAGE_NAME=$1

# Wyszukiwanie pakietu w portage
echo "Wyszukiwanie pakietu: $PACKAGE_NAME..."
emerge -s $PACKAGE_NAME

# Alternatywnie, jeśli chcesz używać equery do szczegółowych informacji
echo "Szczegóły pakietu:"
equery l $PACKAGE_NAME

